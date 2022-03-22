#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include "client.h"

Client::Client(vector<Client*>* clients, vector<Room*>* rooms) : clients(clients), rooms(rooms) {}

void Client::talk() {
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
            delete socket;

            break;
        }

        string token = msg.substr(0, 4);
        string content = msg.substr(5, string::npos);

        if(token == "DISC") {
            onDiscRqc();
        } else if(token == "JOIN") {

        } else if(token == "SEND") {
            //dl
            /*for(StreamSocket* s : *socket) {
                if(c == socket)
                    continue;

                c->send(content);
            }   */
            //fl
        } else {
            socket->send("Your request hasn't been recognized\n");
        }
    }

    google::protobuf::ShutdownProtobufLibrary();

    return;
}

void Client::onDiscRqc() {
    RoomsListProto roomsList;
    for(Room* r : *rooms) {
        RoomProto* roomProto = roomsList.add_room();
        for(Client* c : *clients) {
            PlayerProto* player = roomProto->add_player();
            player->set_id(c->getId());
            player->set_pseudo(c->getPseudo());
        }
    }

    socket->send("DISC" + roomsList.SerializeAsString());
}
