#include <iostream>
#include <thread>
#include <vector>

#include <sys/time.h>
#include "socket.h"
#include "client.h"
#include "room.h"

using namespace std;
using namespace stdsock;

#define MAX_CLIENTS 5

int main(int argc, char *argv[])
{   
    vector<Client*> clients;
    vector<Room*> rooms;
    
    int port;
    if(argc!=2 || sscanf(argv[1], "%d", &port)!=1)
    {
        printf("usage: %s port\n", argv[0]);
        // default port, if none provided
        port= 3390;
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
        StreamSocket *sock=server->accept();

        if (!sock->valid()) {
            delete sock;
            continue;
        }

        if(clients.size() >= MAX_CLIENTS) {
            sock->send("The server is full, please come back later\n");
            delete sock;
            continue;
        }

        cout << "Client connected on fd : " << sock->getSockfd() << endl;

        Client* client = new Client(&clients, &rooms);
        client->setsocket(sock);

        clients.push_back(client);

       thread th = std::thread(&Client::talk, client);
       th.detach();
    }
}
