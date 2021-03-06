#include "room.h"

int32_t Room::nextId = 0;

Room::Room() : id(nextId++), state(WAIT)
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

void Room::init() {
    //init lives
    nbLives = clients->size();

    //init shur
    nbShurs = 1;

    // init cards
    for (size_t i = 1; i <= 100; i++)
    {
        cards.push_back(i);
    }
    
    // init levels bonuses
    levels.push_back(Level{ NONE }); //first level
    for (size_t i = 0; i < MAX_LEVELS; i++)
    {
        if (i < 10)
            levels.push_back(Level{ static_cast<Bonus>(NONE + i % 3) });
        else
            levels.push_back(Level{ NONE });
    }
}


void Room::start() {
    cout << "Starting the game for the room " << id << " " << name << endl;
    
    init();

    for(Client* c : *clients) {
        // start the game and give as many lives as players
        c->send("STRT " + to_string(nbLives) + " " + to_string(nbShurs) + '\0');
        c->setWaitingForAck(true);
    }
}

void Room::deal() {
    cout << "Dealing the cards for the room " << id << " " << name << ". Round : " << MAX_LEVELS - levels.size() + 2 << "/" << MAX_LEVELS << endl;
    // put the played cards back in the main deck
    while(!playedCards.empty()) {
        cards.push_back(playedCards.back());
        playedCards.pop_back();
    }

    //shuffle the cards
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(cards.begin(), cards.end(), default_random_engine(seed));
    
    // get the bonus corresponding to the level
    Bonus bonus = levels.front().bonus;
    levels.erase(levels.begin());

    if (bonus == LIFE)
    {
        if(nbLives < MAX_LIVES)
            nbLives++;
        else
            bonus = NONE;
    }
    else if (bonus == SHUR)
    {
        if(nbShurs < MAX_SHURS)
            nbShurs++;
        else
            bonus = NONE;
    }
    

    // deal the cards
    for(Client* client : *clients) {
        vector<int> * clientCards = client->getCards();
        for (size_t i = 0; i <= MAX_LEVELS - levels.size(); i++)
        {
            clientCards->push_back(cards.back());
            cards.pop_back();
        }

        sort(clientCards->begin(), clientCards->end());

        // genereate cards list proto
        CardsListProto cardsListProto;
        for(int32_t card : *clientCards) {
            CardProto* cardProto = cardsListProto.add_card();
            cardProto->set_value(card);
        }

        // send the bonus and the cards to the client
        client->send("DEAL " + to_string(bonus) + " " + cardsListProto.SerializeAsString());
        client->setWaitingForAck(true);
    }

    cout << "Dealing the cards in the room " << id << " " << name << " and bonus is " << bonus << endl;
}
void Room::putCard(int32_t idClient, int32_t card) {
    playedCards.push_back(card);

    for(Client* c : *clients) {
        c->send("PUT_ " + to_string(idClient) + " " + to_string(card) + '\0');
        c->setWaitingForAck(true);
    }    

    // check if other players have lower cards (bad order)
    PlayerCardsMapProto map;
    for(Client* client : *clients) {
        vector<int>* clientCards = client->getCards();
        CardsListProto lowerCards;

        // find, for each client, their lower cards
        for(int32_t c : *clientCards) {
            if(c < card) {
                CardProto* cardProto = lowerCards.add_card();
                cardProto->set_value(c);
            }
        }

        // remove the lower cards from the client's cards
        for (size_t i = 0; i < (unsigned)lowerCards.card_size(); i++)
        {
            clientCards->erase(clientCards->begin());
        }
        
        // add the lower cards to the proto map
        if (lowerCards.card_size() > 0) {
            auto& mapCards = *map.mutable_cards();
            mapCards[client->getId()] = lowerCards;
        }
    }

    // if so, trigger BADO
    if (map.cards_size() > 0)
    {
        cout << "Player " << idClient << " caused a bad order in the room " << id << " " << name << endl;
        for(Client* client : *clients) {
            client->send("BADO " + map.SerializeAsString());
            client->setWaitingForAck(true);
        }

        nbLives--;
        // if the game is lost, go back to waiting room
        if(nbLives <= 0) {
            state = WAIT;
            return;
        }
    }

    // check if the players don't have anymore cards
    bool lastCard = true;
    for(Client* client : *clients) {
        if(!client->getCards()->empty())
            lastCard = false;
    }

    if (lastCard)
    {
        cout << "Round : " << MAX_LEVELS - levels.size() + 1 << "/" << MAX_LEVELS << " has been won in the room " << id << " " << name << endl;
        deal();
        return;
    }
}

void Room::onShurRpl(string reply) {
    if (reply == "OK__") {
        // check if everybody is ok to use the shur
        for(Client * c : *clients) {
            if(c->isOkForShur() == false)
                return;
        }

        // if so, set everyone's shur to false again...
        for(Client * c : *clients) {
            c->setShur(false);
        }

        // set the state back to play
        state = PLAY;

        // and send the result
        PlayerCardsMapProto map;
        auto& mapCards = *map.mutable_cards();
        for(Client * c : *clients) {
            CardsListProto lowestCard;
            CardProto* card = lowestCard.add_card();
            card->set_value(*c->getCards()->begin());

            // remove the first card
            if(!c->getCards()->empty())
                c->getCards()->erase(c->getCards()->begin());

            mapCards[c->getId()] = lowestCard;
        }

        for(Client * c : *clients) {
            c->send("RES_ OK__ " + map.SerializeAsString());
            c->setWaitingForAck(true);
        }

        // check if the players don't have anymore cards
        bool lastCard = true;
        for(Client* client : *clients) {
            if(!client->getCards()->empty())
                lastCard = false;
        }

        if (lastCard)
        {
            cout << "Round : " << MAX_LEVELS - levels.size() + 1 << "/" << MAX_LEVELS << " has been won in the room " << id << " " << name << endl;
            deal();
            return;
        }
    } else {
        state = PLAY;

        for(Client * c : *clients) {
            c->send("RES_ NOK_ ");
            c->setWaitingForAck(true);
        }
    }
}
