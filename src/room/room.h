#pragma once

#include <iostream>
#include <vector>
#include "client.h"

#ifndef ROOM_H
#define ROOM_H

#pragma once

using namespace std;

class Client;
class Room
{
public:
    Room();
    ~Room();
    vector<Client*>* getClients() { return clients; }
private:
    int32_t id;
    string name;
    vector<Client*>* clients;
};

#endif