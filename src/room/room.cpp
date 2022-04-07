#include "room.h"

int32_t Room::nextId = 0;

Room::Room() : id(nextId++)
{
    clients = new vector<Client*>();

    // init cards
    for (size_t i = 1; i <= 100; i++)
    {
        cards.push_back(i);
    }

    // init levels bonuses
    for (size_t i = 0; i < MAX_LEVELS; i++)
    {
        if (i < 10)
            levels.push(Level{ static_cast<Bonus>(NONE + i % 3) });
        else
            levels.push(Level{ NONE });
    }
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


void Room::start() {
    for(Client* c : *clients) {
        // start the game and give as many lives as players
        c->send("STRT " + to_string(clients->size()) + '\0');
        c->setWaitingForAck(true);
    }
}

void Room::deal() {
    // put the played cards back in the main deck
    while(!playedCards.empty()) {
        cards.push_back(playedCards.back());
        playedCards.pop_back();
    }

    //shuffle the cards
    random_shuffle(cards.begin(), cards.end());
    
    // get the bonus corresponding to the level
    Bonus bonus;
    if (levels.size() >= MAX_LEVELS) // if it's the first round, don't give any bonus
        bonus = NONE;
    else {
        bonus = levels.top().bonus;
        levels.pop();
    }

    // deal the cards
    for(Client* client : *clients) {
        for (size_t i = 0; i <= MAX_LEVELS - levels.size(); i++)
        {
            client->getCards()->push_back(cards.back());
            cards.pop_back();
        }

        // genereate cards list proto
        CardsListProto cardsListProto;
        for(int32_t card : *client->getCards()) {
            CardProto* cardProto = cardsListProto.add_card();
            cardProto->set_value(card);
        }

        // send the bonus and the cards to the client
        client->send("DEAL " + to_string(bonus) + " " + cardsListProto.SerializeAsString());
        client->setWaitingForAck(true);
    }
}