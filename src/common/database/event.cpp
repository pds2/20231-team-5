#include "../../../include/common/services/event_service.h"
#include "../../../include/common/services/extra_points_event.h"
#include "../../../include/common/services/delete_player_event.h"

#include <iostream>

EventService::EventService()
{
    //this->events = events;

    ExtraPointsEvent* event1 = new ExtraPointsEvent();
    DeletePlayerEvent* event2 = new DeletePlayerEvent();

    addEvent(event1);
    addEvent(event2);
}

EventService::~EventService(){
    for (Event* event : this->events){
        delete event;
    }
}

void EventService::addEvent(Event *event)
{
    this->events.push_back(event);
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
            std::cout << currentEvent->getName() << std::endl;
            return true;
        }
    }

    return false;
}

void EventService::runCurrentEvent(unsigned int score, PlayerService* player_service, ScoreboardService* scoreboard_service){
    std::cout << currentEvent->getName() << std::endl;
    currentEvent->run(score, player_service, scoreboard_service);
}

