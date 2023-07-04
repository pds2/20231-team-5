#include "../../../include/common/services/event_service.h"

EventService::EventService(vector<Event*> events){
    this->events = events;
}

EventService::~EventService(){
    for (Event* event : this->events){
        delete event;
    }
}



Event* EventService::getEvent(string event_name){
    for (Event* event : this->events){
        if (event->getName() == event_name){
            return event;
        }
    }

    throw EventDoesNotExistException();
}

void EventService::run(PlayerService* player_service, ScoreboardService* scoreboard_service){
    for (Event* event : this->events){
        if (event->canRun()){
            event->run(player_service, scoreboard_service);
        }
    }
}

