#include "../../../include/common/database/event.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

Event::Event(EventType type){
    this->type = type;
    this->active = true;
}

Event::~Event() {}


EventType Event::getType(){
    return this->type;
}

bool Event::isActive(){
    return this->active;
}

void Event::enable(){
    this->active = true;
}

void Event::disable(){
    this->active = false;
}

string Event::getName(){
    return "Evento Genérico";
}

string Event::getDescription(){
    return "Evento Genérico do Jogo";
}

bool Event::canRun(){
    if (this->type != EventType::RANDOM){
        throw EventTypeMismatchException();
    }

    if (this->active == false){
        return false;
    }

    // Gera um numero aleatorio entre 0 e 9
    std::srand(std::time(nullptr));
    int random_number = std::rand() % 10; 
    
    if (random_number == 1){ // 10% de chance de acontecer
        return true;
    }
    return false;
}