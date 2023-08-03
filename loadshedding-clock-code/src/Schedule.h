#ifndef SCHEUDLE_H
#define SCHEDULE_H

#include "Arduino.h"
#include "Event.h"
#include "storage.h"
#include "dateTime.h"

/**
 * Shedule class
 * 
 * This class is used to represent the loadshedding schedule.
 * 
 * @param events An array of Events.
 * @param numberOfEvents The number of events in the schedule.
 */
class Schedule
{
private:
    Event *events;
public:
    int numberOfEvents;
    Schedule();
    void update();
    boolean isCurrentlyLoadshedding();
    int getSecondsUntilNextTransition();
    int getHighestUpcomingStage();
    int getHighestStageOfToday();
};

#endif