#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include "client.h"

int32_t Client::nextId = 0;

vector<string> splitString(string str, string delimiter = " ");

Client::Client(vector<Client*>* clients, vector<Room*>* rooms) : clients(clients), rooms(rooms), id(nextId++) {}

Client::~Client() {
    delete socket;

    google::protobuf::ShutdownProtobufLibrary();
}

void Client::run() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    int len;

    //TODO: corriger le bug : 1 seul client, envoie deux fois des messages.
    while(true)
    {
        string msg;
        len = socket->read(msg);
        if(len <= 0) {
            //La connexion est coupee du cote du client ou erreur
            //dr
            clients->erase(std::remove(clients->begin(), clients->end(), this), clients->end());
            //fr
            cout << "Client disconnected of fd : " << socket->getSockfd() << endl;

            delete this;

            return;
        }

        if(msg.size() < 4) {
            socket->send("ERR_ 1");
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
        } else if(token == "SEND") {
            //dl
            /*for(StreamSocket* s : *socket) {
                if(c == socket)
                    continue;

                c->send(content);
            }   */
            //fl
        } else {
            socket->send("ERR_ 1");
        }
    }
}

void Client::onDiscRqc() {
    RoomsListProto roomsList;
    for(Room* r : *rooms) {
        RoomProto* roomProto = roomsList.add_room();
        roomProto->set_id(r->getId());
        roomProto->set_name(r->getName());
        for(Client* c : *r->getClients()) {
            PlayerProto* player = roomProto->add_player();
            player->set_id(c->getId());
            player->set_pseudo(c->getPseudo());
        }
    }
    
    socket->send("DISC " + roomsList.SerializeAsString());

    cout << roomsList.DebugString() << endl;
}

void Client::onCreaRqc(string msg) {
    vector<string> args = splitString(msg, " ");
    string roomName = args[0];
    string nbPlayers = args[1];
    pseudo = args[2];
    
    Room* room = new Room();
    room->setName(roomName);
    room->setNbMaxPlayers(stoi(nbPlayers));
    room->getClients()->push_back(this);
    rooms->push_back(room);

    socket->send("CREA " + to_string(room->getId()) + " " + to_string(id) + '\n');
}

void Client::onJoinRqc(string msg) {
    vector<string> args = splitString(msg, " ");
    string roomId = args[0];
    pseudo = args[1];

    Room* room = Room::findRoomById(rooms, stoi(roomId));

    if(room == nullptr) {
        socket->send("ERRO 31");
        return;
    }

    if((int)room->getClients()->size() >= room->getNbMaxPlayers()) {
        socket->send("ERRO 32");
        return;
    }

    room->getClients()->push_back(this);

    RoomProto roomProto;
    for(Client* c : *room->getClients()) {
        PlayerProto* p = roomProto.add_player();
        p->set_id(c->getId());
        p->set_pseudo(c->getPseudo());
    }

    socket->send(roomProto.SerializeAsString() + " " + to_string(id));
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