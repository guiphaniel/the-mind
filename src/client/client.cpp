#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include "client.h"

void TalkServer::talk() {
    int len;

    //TODO: corriger le bug : 1 seul client, envoie deux fois des messages.
    while(true)
    {
        string msg;
        len = client->read(msg);
        if(len <= 0) {
            //Si la connexion est coupee du cote du client, on retire le fd correspondant des destinataires
            //dr
            clients->erase(std::remove(clients->begin(), clients->end(), client), clients->end());
            //fr
            cout << "Client disconnected of fd : " << client->getSockfd() << endl;
            delete client;

            break;
        }

        string token = msg.substr(0, 4);
        string content = msg.substr(5, string::npos);

        if(token == "DISC") {

        } else if(token == "JOIN") {

        } else if(token == "SEND") {
            //dl
            for(StreamSocket* c : *clients) {
                if(c == client)
                    continue;

                c->send(content);
            }   
            //fl
        } else {
            client->send("Your request hasn't been recognized\n");
        }
    }

    return;
}

