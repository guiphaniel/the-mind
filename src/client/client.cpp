#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include "client.h"

int32_t Client::nextId = 0;

vector<string> splitString(string str, string delimiter = " ");

Client::Client(vector<Client*>* clients, vector<Room*>* rooms) : clients(clients), rooms(rooms), room(nullptr), id(nextId++), focus(false), shur(false), waitingForAck(false) {
    cards = new vector<int32_t>;
}

Client::~Client() {
    //dr
    clients->erase(std::remove(clients->begin(), clients->end(), this), clients->end());
    //fr
    if (room != nullptr)
    {
        // leave the room
        vector<Client*>* roomClients = room->getClients();
        roomClients->erase(std::remove(roomClients->begin(), roomClients->end(), this), roomClients->end());

        // if th room is empty, remove it
        if(roomClients->size() <= 0) {
            rooms->erase(std::remove(rooms->begin(), rooms->end(), room), rooms->end());
            cout << "Client " << id << " " << pseudo << " has left the room " << room->getId() << " " << room->getName() << " " << room->getClients()->size() << "/" << room->getNbMaxPlayers() << endl;
            delete room;
        }
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

            socket->close();

            if(room == nullptr || room->getClients()->size() <= 1) // the client was not in a room, or was the last one in it
                delete this;
            else {
                // check if all remaining clients are disconnected
                bool allDisconnected = true;
                for(Client* c : *room->getClients()) {
                    if (c->getSocket()->valid())
                    {
                        allDisconnected = false;
                        break;
                    }
                }

                // if so, delete them all.
                if (allDisconnected)
                {
                    for(Client* c : *room->getClients())
                        delete c;
                    return;
                }
                
                // else, jsut warn others that this client disconnected
                room->setState(LEFP);

                socket->close();
                
                for(Client* c : *room->getClients()){
                    c->send("LEFP " + to_string(id) + '\0');
                    c->setWaitingForAck(true);
                }
            }

            return;
        }

        if(msg.size() < 4) {
            send("ERRO 1");
            continue;
        }
        string token = msg.substr(0, 4);
        
        if(token == "DISC") {
            thread(&Client::onDiscRqc, this).detach();
        } else if(token == "CREA") {
            string content = msg.substr(5, string::npos);
            thread(&Client::onCreaRqc, this, content).detach();
        } else if(token == "JOIN") {
            string content = msg.substr(5, string::npos);
            thread(&Client::onJoinRqc, this, content).detach();
        } else if(token == "QUIT") {
            thread(&Client::onQuitRqc, this).detach();
        } else if(token == "FOCU") {
            thread(&Client::onFocuRqc, this).detach();
        } else if(token == "PUT_") {
            int32_t card = stoi(msg.substr(5, string::npos));
            thread(&Client::onPutRqc, this, card).detach();
        } else if(token == "SHUR") {
            thread(&Client::onShurRqc, this).detach();
        } else if(token == "OK__" || token == "NOK_") {
            thread(&Client::onShurRpl, this, token).detach();
        } else if(token == "RECO") {
            vector<string> args = splitString(msg, " ");
            thread(&Client::onRecoRqc, this, stoi(args[0]), stoi(args[1])).detach();
        } else if(token == "ACK_") {
            setWaitingForAck(false);
        } else {
            send("ERRO 1");
        }
    }
}

int Client::send(const std::string& msg) {
    if(socket == nullptr || !socket->valid())
        return -1;

    unique_lock<std::mutex> lk(waitMutex);
    waitCv.wait(lk, [&]{return !isWaitingForAck();});
    return socket->send(msg);
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
    cards->clear();
    vector<Client*>* roomClients = room->getClients();
    roomClients->erase(std::remove(clients->begin(), clients->end(), this), clients->end());

    // if the client was the last one in the room, remove the room
    if(roomClients->size() <= 0) {
        rooms->erase(std::remove(rooms->begin(), rooms->end(), room), rooms->end());
        cout << "Client " << id << " " << pseudo << " has left the room " << room->getId() << " " << room->getName() << " " << room->getClients()->size() << "/" << room->getNbMaxPlayers() << endl;
        delete room;
        room = nullptr;
        send("ACK_");
        return;
    }

    // check if all remaining clients in the room are disconnected
    bool allDisconnected = true;
    for(Client* c : *room->getClients()) {
        if (c->getSocket()->valid())
        {
            allDisconnected = false;
            break;
        }
    }

    // if so, delete them all.
    if (allDisconnected)
    {
        for(Client* c : *room->getClients()) {
            delete c;
        }
    }
    
    send("ACK_");

    for(Client* c : *room->getClients()){
        c->send("LEFP " + to_string(id) + '\0');
        c->setWaitingForAck(true);
    }

    room = nullptr;
    
    cout << "Client " << id << " " << pseudo << " has left the room " << room->getId() << " " << room->getName() << " " << room->getClients()->size() << "/" << room->getNbMaxPlayers() << endl;
}

void Client::onFocuRqc() {
    cout << "Client " << id << " " << pseudo << " focused" << endl;
    if (room->getState() == PLAY) {
        room->setState(FOCU);
    }
        
    focus = true;

    send("ACK_");

    // warn other clients that this one focused
    for(Client* c : *room->getClients()) {
        c->send("FOCU " + to_string(id)); //TODO: '\0' ?
        c->setWaitingForAck(true);
    }

    // check if all clients are focused
    for(Client* c : *room->getClients()) {
        if(!c->getSocket()->valid()) // if the player is disconnected, skip him
            continue;

        if(!c->isFocused())
            return;
    }
    
    // if so, resume the game
    room->setState(PLAY);
    
    // if some clients were disconnected, delete them
    for(Client* c : *room->getClients()) {
        if(!c->getSocket()->valid())
            delete c;
    }

    for(Client* c : *room->getClients()) {
        c->setFocus(false);
        c->send("RESM");
    }
    cout << "Everyone in room " << room->getId() << " " << room->getName() << " is now focused. Resuming the game..." << endl;
}

void Client::onPutRqc(int32_t card) {
    // check if the game is playing
    if (room->getState() != PLAY) {
        send("ERRO 43");
        return;
    }   

    // check if the client has this card
    if(!count(cards->begin(), cards->end(), card)) {
        send("ERRO 41");
        return;
    }

    // check if the card played is the smallest card of the player
    if(card != *cards->begin()) {
        send("ERRO 42");
        return;
    }

    send("ACK_");
    cout << "Client " << id << " " << pseudo << " in room " << room->getId() << " " << room->getName() << " has played the card " << card << endl;
    
    cards->erase(cards->begin());
    
    room->putCard(id, card);    
}

void Client::onShurRqc() {
    // check if the game is playing
    if (room->getState() != PLAY) {
        send("44");
        return;
    }  

    cout << "Client " << id << " " << pseudo << " in room " << room->getId() << " " << room->getName() << " has asked for the use of a shuriken." << endl;
    
    send("ACK_");

    shur = true;
    room->setState(SHURI);
    for(Client * c : *room->getClients()) {
        c->send("SHUR " + to_string(id));
    }
}

void Client::onShurRpl(string reply) {
    if (reply == "OK__") {
        shur = true;
    }

    room->onShurRpl(reply);
}

void Client::onRecoRqc(int32_t roomId, int32_t clientId) {
     cout << "Client " << to_string(clientId) << " asked for a reconnection in the room " << to_string(roomId) << endl;

    // check if the room exists
    Room* room = Room::findRoomById(rooms, roomId);
    if (room == nullptr) {
        send("ERRO 31");
        return;
    }
    
    // check if he was in the room, and if the room is still waiting for him
    Client* client = room->findPlayerById(clientId);
    if (client == nullptr) {
        send("ERRO 34");
        return;
    }
    
    // replace the old client by this new one
    id = client->id;
    pseudo = client->pseudo;
    cards = client->cards;
    room = client->room;
    delete client;
    room->getClients()->push_back(this);

    cout << "Client " << id << " " << pseudo << " reconnected in the room " << room->getId() << " " << room->getName() << " " << room->getClients()->size() << "/" << room->getNbMaxPlayers() << endl;

    // send the room infos to the reconnecting client
    PlayerCardsMapProto playersCards;
    for(Client* client : *room->getClients()) {
        CardsListProto playerCards;
        for(int32_t card : *client->getCards()) {
            CardProto* cardProto = playerCards.add_card();
            cardProto->set_value(card);
        }
        auto& mapCards = *playersCards.mutable_cards();
        mapCards[client->getId()] = playerCards;
    }

    send("STAT " + to_string(room->getCurrentLevel()) + " " + to_string(room->getLastPlayedCard()) + " " + to_string(room->getNbLives()) + " " + to_string(room->getNbShurs()) + " " + playersCards.SerializeAsString());
    setWaitingForAck(true);
    
    // warn other clients
    for(Client * c : *room->getClients()) {
        if(c == this)
            continue;

        send("RECP " + to_string(id));
        c->setWaitingForAck(true);
    }

    //resume the game
    room->setState(PLAY);
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