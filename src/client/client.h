#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include "socket.h"
#include "room.h"
#include "player.pb.h"
#include "rooms_list.pb.h"
#include "cards_list.pb.h"

#ifndef TALK_SERVER_H
#define TALK_SERVER_H

using namespace std;
using namespace stdsock;
using namespace protos;

class Room;
class Client
{
private:
    StreamSocket* socket;
    // have a reference of all clients, to remove self from it when connection is closed
    vector<Client*>* clients;
    // have a reference too all rooms, to add/remove a room from them when necessary
    vector<Room*>* rooms;
    Room* room;
    static int32_t nextId;
    int32_t id;
    string pseudo;
    vector<int32_t> cards;
    bool focus;

    void onDiscRqc();
    void onCreaRqc(string msg);
    void onJoinRqc(string msg);
    void onQuitRqc();
    void onFocuRqc();
public:
    Client(vector<Client*>* clients, vector<Room*>* rooms);
    ~Client();

    StreamSocket* getSocket() const { return socket;}
    void setSocket(StreamSocket* s) { socket=s; }

    vector<Client*>* getClients() const { return clients;}
    void setClients(vector<Client*>* cs) { clients = cs; }

    vector<Room*>* getRooms() const { return rooms;}
    void setRooms(vector<Room*>* rs) { rooms = rs; }

    int32_t getId() {return id;};
    void setId(int32_t _id) {id = _id;}

    string getPseudo() {return pseudo;};
    void setPseudo(string p) {pseudo = p;}

    vector<int32_t> getCards() const { return cards; }

    void run();

    bool isFocused() const { return focus; }
    void setFocus(bool focus_) { focus = focus_; }
};

#endif // TALK_H