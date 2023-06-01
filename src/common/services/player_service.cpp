#include "../include/common/services/player_service.h"

PlayerService::PlayerService() {
    this->players = vector<Player>();
    this->current_player_id = 0;
}

void PlayerService::addPlayer(string name) {
    unsigned int id = 0;
    if (!this->players.empty()) {  // Não vazio
        id = this->players.back().getId() + 1;
    }

    Player player = Player(id, name);
    this->players.push_back(player);
}

Player& PlayerService::getPlayer(unsigned int id) {
    return this->players[id];
}

Player& PlayerService::getCurrentPlayer() {
    if (this->players.empty()) {
        throw NoPlayersException();
    }

    return this->getPlayer(this->current_player_id);
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