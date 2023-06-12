#include "../../../include/common/database/player.h"
#include <locale>
#include <codecvt>

Player::Player(unsigned int id, string name){
    this->id = id;
    if(name.length() > 15){
        throw InvalidNameException();
    }

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    if(name.length() != converter.from_bytes(name).length()){
        // Nome com caracteres especiais
        throw InvalidNameException();
    }
    this->name = name;
    this->is_playing = true;
}

unsigned int Player::getId(){
    return this->id;
}

string Player::getName(){
    return this->name;
}

bool Player::isPlaying(){
    return this->is_playing;
}

void Player::eliminate(){
    this->is_playing = false;
}

