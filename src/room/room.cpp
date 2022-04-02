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
    for(Room* r : *rooms) {
        if(r->getId() == id)
            return r;
    }
    return nullptr;
}

Client* Room::findPlayerById(int32_t id) {
    for(Client* c : *clients) {
        if(c->getId() == id)
            return c;
    }
    return nullptr;
}
