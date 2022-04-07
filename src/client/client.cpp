#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include "client.h"

int32_t Client::nextId = 0;

vector<string> splitString(string str, string delimiter = " ");

Client::Client(vector<Client*>* clients, vector<Room*>* rooms) : clients(clients), rooms(rooms), room(nullptr), id(nextId++), focus(false) {
    cards = new vector<int32_t>;
    waitingForAck = false;
}

Client::~Client() {
    //dr
    clients->erase(std::remove(clients->begin(), clients->end(), this), clients->end());
    //fr
    if (room != nullptr)
    {
        vector<Client*>* roomClients = room->getClients();
        roomClients->erase(std::remove(roomClients->begin(), roomClients->end(), this), roomClients->end());
    }

    delete cards;
    delete socket;
}

void Client::run() {
    int len;

    while(true)
    {
        string msg;
        len = socket->read(msg);
        if(len <= 0) {
            //La connexion est coupee du cote du client ou erreur
            cout << "Client disconnected of fd : " << socket->getSockfd() << endl;

            delete this;

            return;
        }

        if(msg.size() < 4) {
            send("ERRO 1");
            continue;
        }
        string token = msg.substr(0, 4);
        
        if(token == "DISC") {
            onDiscRqc();
        } else if(token == "CREA") {
            string content = msg.substr(5, string::npos);
            onCreaRqc(content);
        } else if(token == "JOIN") {
            string content = msg.substr(5, string::npos);
            onJoinRqc(content);
        } else if(token == "QUIT") {
            onQuitRqc();
        } else if(token == "FOCU") {
            onFocuRqc();
        } else if(token == "PUT_") {
            onPutRqc(stoi(msg.substr(5, string::npos)));
        } else if(token == "ACK_") {
            setWaitingForAck(false);
        } else {
            send("ERRO 1");
        }
    }
}

void Client::send(const std::string& msg) {
    unique_lock<std::mutex> lk(waitMutex);
    waitCv.wait(lk, [&]{return !isWaitingForAck();});
    socket->send(msg);
}

void Client::onDiscRqc() {
    RoomsListProto roomsList;
    for(Room* r : *rooms) {
        RoomProto* roomProto = roomsList.add_room();
        roomProto->set_id(r->getId());
        roomProto->set_name(r->getName());
        roomProto->set_nb_max_players(r->getNbMaxPlayers());
        for(Client* c : *r->getClients()) {
            PlayerProto* player = roomProto->add_player();
            player->set_id(c->getId());
            player->set_pseudo(c->getPseudo());
        }
    }
    
    send("DISC " + roomsList.SerializeAsString());

    cout << "Client " << id << " " << pseudo << " requested for a discovery." << endl;
    cout << roomsList.DebugString() << endl;
}

void Client::onCreaRqc(string msg) {
    vector<string> args = splitString(msg, " ");
    string roomName = args[0];
    string nbPlayers = args[1];
    pseudo = args[2];

    // errors verifications
    if (stoi(nbPlayers) < 2 || stoi(nbPlayers) > MAX_ROOM_SIZE)
    {
        send("ERRO 2");
        return;
    }
    
    room = new Room();
    room->setName(roomName);
    room->setNbMaxPlayers(stoi(nbPlayers));
    room->getClients()->push_back(this);
    rooms->push_back(room);

    send("CREA " + to_string(room->getId()) + " " + to_string(id) + '\0');
    setWaitingForAck(true);
    cout << "Client " << to_string(getId()) << " " << getPseudo() << " requested for a room creation : " << room->getId() << " " << roomName << " 0/" << nbPlayers << endl;
}

void Client::onJoinRqc(string msg) {
    vector<string> args = splitString(msg, " ");
    string roomId = args[0];
    pseudo = args[1];

    room = Room::findRoomById(rooms, stoi(roomId));   

    // errors verifications
    if(room == nullptr) {
        send("ERRO 31");
        return;
    }

    if(room->getClients()->size() >= (unsigned)room->getNbMaxPlayers()) {
        send("ERRO 32");
        return;
    }

    if (room->findPlayerById(id) == this)
    {
        send("ERRO 33");
        return;
    }

    if (room->getState() != WAIT)
    {
        send("ERRO 34");
        return;
    }

    // warn other players that a new player joined the room
    PlayerProto newPlayer;
    newPlayer.set_id(id);
    newPlayer.set_pseudo(pseudo);
    for(Client* c : *room->getClients()) {
        c->send("NEWP " + newPlayer.SerializeAsString());
        c->setWaitingForAck(true);
    }

    // add player to the room
    room->getClients()->push_back(this);

    // send room informations to the player
    RoomProto roomProto;
    roomProto.set_id(room->getId());
    roomProto.set_name(room->getName());
    roomProto.set_nb_max_players(room->getNbMaxPlayers());
    for(Client* c : *room->getClients()) {
        PlayerProto* p = roomProto.add_player();
        p->set_id(c->getId());
        p->set_pseudo(c->getPseudo());
    }

    send("JOIN " + to_string(id) + " " + roomProto.SerializeAsString());
    setWaitingForAck(true);
    cout << "Client " << id << " " << pseudo << " joined room " << room->getId() << " " << room->getName() << " " << room->getClients()->size() << "/" << room->getNbMaxPlayers() << endl;

    // if the room is full, start the game
    if (room->getClients()->size() >= (unsigned)room->getNbMaxPlayers())
    {
        room->start();
        room->deal();
    }
}

void Client::onQuitRqc() {
    vector<Client*>* clients = room->getClients();
    clients->erase(std::remove(clients->begin(), clients->end(), this), clients->end());

    if(clients->size() <= 0) {
        rooms->erase(std::remove(rooms->begin(), rooms->end(), room), rooms->end());
        delete room;
        room = nullptr;
        send("ACK_");
        return;
    }
    
    send("ACK_");

    for(Client* c : *room->getClients()){
        c->send("LEFP " + to_string(id) + '\0');
    }

    room = nullptr;
}

void Client::onFocuRqc() {
    if (room->getState() == PLAY)
        room->setState(FOCU);

    focus = true;

    // check if all clients are focused
    for(Client* c : *room->getClients()) {
        if(!c->isFocused())
            return;
    }
    
    // if so, resume the game
    room->setState(PLAY);
    for(Client* c : *room->getClients()) {
        c->send("RESM");
    }
}

//TODO:
void Client::onPutRqc(int32_t card) {
    // check if the client has this card
    if(!count(cards->begin(), cards->end(), card)) {
        send("ERRO 4");
        return;
    }

    
}

vector<string> splitString(string str, string delimiter)
{
    vector<string> args;
    int start = 0;
    int end = str.find(delimiter);
    while (end != -1) {
        args.push_back(str.substr(start, end - start));
        start = end + delimiter.size();
        end = str.find(delimiter, start);
    }
    args.push_back(str.substr(start, end - start));

    return args;
}