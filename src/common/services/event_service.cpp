#include "../../../include/common/services/event_service.h"
#include "../../../include/common/services/extra_points_event.h"
#include "../../../include/common/services/delete_player_event.h"

#include <iostream>

EventService::EventService()
{
    //this->events = events;

    ExtraPointsEvent* event1 = new ExtraPointsEvent();
    //DeletePlayerEvent* event2 = new DeletePlayerEvent();
    std::cout<<"aqui foi"<<std::endl;
    std::cin.get();
    addEvent(event1);
    std::cout<<"aqui foi 2"<<std::endl;
    std::cin.get();
    //addEvent(event2);
    // std::cout<<"aqui foi 3"<<std::endl;
    // std::cin.get();

}

EventService::~EventService(){
    for (Event* event : this->events){
        delete event;
    }
}

void EventService::addEvent(Event *event)
{
    std::cout<<"aqui foi 3"<<std::endl;
    std::cin.get();
    this->events.push_back(event);
    std::cout<<"aqui foi 4"<<std::endl;
    std::cin.get();
}


Event* EventService::getEvent(string event_name){
    for (Event* event : this->events){
        if (event->getName() == event_name){
            return event;
        }
    }

    throw EventDoesNotExistException();
}

/*
void EventService::run(PlayerService* player_service, ScoreboardService* scoreboard_service){
    for (Event* event : this->events){
        if (event->canRun()){
            event->run(player_service, scoreboard_service);
        }
    }



*/
bool EventService::getRunnableEvent(){
    for(Event* event : this->events){
        if(event->canRun()){
            currentEvent = event;
            return true;
        }
    }

    return false;
}

void EventService::runCurrentEvent(unsigned int score, PlayerService* player_service, ScoreboardService* scoreboard_service){
    currentEvent->run(score, player_service, scoreboard_service);
}

