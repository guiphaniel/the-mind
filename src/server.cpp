#include <iostream>
#include <thread>
#include <vector>

#include <sys/time.h>
#include "socket.h"
#include "client.h"

using namespace std;
using namespace stdsock;

#define MAX_CLIENTS 3

int main(int argc, char *argv[])
{
    vector<StreamSocket*> clients;

    int port;
    if(argc!=2 || sscanf(argv[1], "%d", &port)!=1)
    {
        printf("usage: %s port\n", argv[0]);
        // default port, if none provided
        port= 3490;
    }

    ConnectionPoint *server=new ConnectionPoint(port);
    int err= server->init();
    if (err != 0) {
        std::cout << strerror(err) << std::endl;
        exit(err);
    }

    cout << "Opened on fd: " << server->getSockfd() << endl;
    cout << "Waiting clients on port " << port << " ..." << endl;

    // accepting connexion
    // and preparing communication points
    while (true)
    {
        TalkServer com;

        StreamSocket *client=server->accept();

        if (!client->valid()) {
            delete client;
            continue;
        }

        if(clients.size() >= MAX_CLIENTS) {
            client->send("The server is full, please come back later\n");
            delete client;
            continue;
        }

        cout << "Client connected on fd : " << client->getSockfd() << endl;

        clients.push_back(client);

        com.setClient(client);
        com.setClients(&clients);

       thread th = std::thread(&TalkServer::talk, com);
       th.detach();
    }
}
