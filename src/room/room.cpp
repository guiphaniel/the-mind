#include "room.h"

Room::Room()
{
    clients = new vector<Client*>();
}

Room::~Room()
{
    delete clients;
}