#include "../include/common/services/player_service.h"
#include <iostream>
using namespace std;

PlayerService::PlayerService() {
    this->players = vector<Player>();
    this->current_player_id = 0;
}

void PlayerService::addPlayer(string name) {
    if(name.empty()) {
        throw InvalidPlayerException();
    }

    if(this->players.size() == this->getMaxPlayerNb()) {
        throw PlayerOverloadException();
    }

    unsigned int id = 0;
    if (!this->players.empty()) {  // Não vazio
        id = this->players.back().getId() + 1;
    }

    Player player = Player(id, name);
    this->players.push_back(player);
}

Player& PlayerService::getPlayer(unsigned int id) {
    if (this->players.empty()) {
        throw NoPlayersException();
    }

    for (Player& player : this->players) {
        if (player.getId() == id) {
            return player;
        }
    }

    throw InvalidPlayerException();
}

Player& PlayerService::getCurrentPlayer() {
    if (this->players.empty()) {
        throw NoPlayersException();
    }

    return this->getPlayer(this->current_player_id);
}

vector<Player*> PlayerService::getPlayers() {
    vector<Player*> players = vector<Player*>();

    for (Player& player : this->players) {
        players.push_back(&player);
    }

    return players;
}

unsigned int PlayerService::getMaxPlayerNb() {
    return 4;
}

void PlayerService::changeCurrentPlayer(){
    if (this->players.empty()) {
        throw NoPlayersException();
    }

    unsigned int last_id = this->players.back().getId();

    if(this->current_player_id == last_id) {
        this->current_player_id = 0;
    } else {
        this->current_player_id++;
    }
}