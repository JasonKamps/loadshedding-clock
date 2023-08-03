#ifndef EVENT_H
#define EVENT_H

#include "Arduino.h"
#include "dateTime.h"

/**
 * Event class
 * 
 * This class is used to represent an event in the schedule.
 * 
 * @param start The start time of the event in seconds since epoch.
 * @param end The end time of the event in seconds since epoch.
 * @param stage The loadshedding stage of the event.
 */
class Event
{
public:
    time_t start;
    time_t end;
    int stage;

    Event();
    Event(time_t start, time_t end, int stage);
    boolean isCurrentlyOccuring();
    int getSecondsUntilNextTransition();
};

#endif