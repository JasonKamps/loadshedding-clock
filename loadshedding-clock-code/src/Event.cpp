#include "Event.h"

// Default constructor
Event::Event()
{
    this->start = 0;
    this->end = 0;
    this->stage = 0;
}

Event::Event(time_t start, time_t end, int stage)
{
    this->start = start;
    this->end = end;
    this->stage = stage;
}

boolean Event::isCurrentlyOccuring()
{
    time_t now = getUnixTime();
    return now >= this->start && now <= this->end;
}

/**
 * Gets the number of seconds until the next transition.
 *
 * @return  If event not started yet, returns seconds until start. If currently loadshedding, returns seconds until end. If event has ended, returns -1.
 */
int Event::getSecondsUntilNextTransition()
{
    time_t now = getUnixTime();

    if (now < this->start)
    {
        // event has not started yet
        return this->start - now;
    }
    else if (now >= this->start && now <= this->end)
    {
        // currently loadshedding
        return this->end - now;
    }

    // event has ended
    return -1;
}
