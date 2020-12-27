#ifndef EVENT_H
#define EVENT_H

#include "point.h"

enum class EventType {Move};

class Event {
public:
    EventType event_type;
    std::shared_ptr<Point> move_target;

    Event(EventType type, std::shared_ptr<Point> target);
    
};

Event::Event(EventType type, std::shared_ptr<Point> target)
        : event_type(type), move_target(target) {

}

#endif
