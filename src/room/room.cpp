#include "room.h"

int32_t Room::nextId = 0;

Room::Room() : id(nextId++)
{
    clients = new vector<Client*>();
}

Room::~Room()
{
    delete clients;
}

Room* Room::findRoomById(vector<Room*>* rooms, int32_t id) {
    return find_if(*rooms->begin(), *rooms->end(), [&](Room room){ return room.getId() == id; });
}