#include "../../../include/common/services/event_service.h"

EventService::EventService()
{
    this->events = events;
    
    // ExtraPointsEvent* event1 = new ExtraPointsEvent();
    // DeletePlayerEvent* event2= new DeletePlayerEvent();

    // addEvent(event1);
    // addEvent(event2);

    //events[0]->run(PlayerService *player_service, ScoreboardService *scoreboard_service);
}

EventService::~EventService(){
    for (Event* event : this->events){
        delete event;
    }
}

void EventService::addEvent(Event* event) {
    events.push_back(event);
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
