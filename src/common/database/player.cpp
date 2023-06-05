#include "../../../include/common/database/player.h"

Player::Player(unsigned int id, string name){
    this->id = id;
    if(name.length() > 15){
        throw InvalidNameException();
    }
    this->name = name;
}

unsigned int Player::getId(){
    return this->id;
}

string Player::getName(){
    return this->name;
}
