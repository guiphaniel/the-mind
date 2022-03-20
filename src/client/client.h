#include <vector>
#include <algorithm>
#include <string>
#include "socket.h"

#ifndef TALK_SERVER_H
#define TALK_SERVER_H

using namespace std;
using namespace stdsock;

class TalkServer
{
private:
    StreamSocket* client;
    vector<StreamSocket*>* clients;
public:
    StreamSocket* getClient() const { return client;}

    void setClient(StreamSocket* c) { client=c; }

    vector<StreamSocket*>* getClients() const { return clients;}

    void setClients(vector<StreamSocket*>* cs) { clients = cs; }

    void talk();
};


#endif // TALK_H