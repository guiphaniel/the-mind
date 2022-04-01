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

    int32_t getId(){return id;}
    void setId(int32_t _id){id = _id;}

    string getName(){return name;}
    void setName(string _name){name = _name;}

    int32_t getNbMaxPlayers(){return nbMaxPlayers;}
    void setNbMaxPlayers(int32_t _nbMaxPlayers){nbMaxPlayers = _nbMaxPlayers;}
    
    vector<Client*>* getClients() { return clients; }

    static Room* findRoomById(vector<Room*>* rooms, int32_t id);
private:
    static int32_t nextId;
    int32_t id;
    string name;
    int32_t nbMaxPlayers;
    vector<Client*>* clients;
};

#endif