#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <random>       // std::default_random_engine
#include <chrono> 
#include "client.h"
#include "player_cards_map.pb.h"

#ifndef ROOM_H
#define ROOM_H

#pragma once

#define MAX_ROOM_SIZE 4
#define MAX_LEVELS 12
#define MAX_LIVES 5
#define MAX_SHURS 3


using namespace std;

enum RoomState { WAIT, FOCU, SHURI, PLAY, LEFP };

enum Bonus { NONE, SHUR, LIFE };

struct Level
{
    Bonus bonus;
};

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

    RoomState getState() const { return state; }
    void setState(const RoomState &state_) { state = state_; }

    int32_t getCurrentLevel() { return MAX_LEVELS - levels.size(); }

    int32_t getLastPlayedCard() { return playedCards.back(); }

    int32_t getNbLives() const { return nbLives; }

    int32_t getNbShurs() const { return nbShurs; }

    static Room* findRoomById(vector<Room*>* rooms, int32_t id);

    Client* findPlayerById(int32_t id);

    void init();
    void start();
    void deal();
    void putCard(int32_t idClient, int32_t card);
    void onShurRpl(string reply);

    mutex clientsMutex;

private:
    static int32_t nextId;
    int32_t id;
    string name;
    int32_t nbMaxPlayers;
    vector<Client*>* clients;
    RoomState state;
    vector<Level> levels;
    int32_t nbLives;
    int32_t nbShurs;
    vector<int32_t> cards;
    vector<int32_t> playedCards;
};

#endif