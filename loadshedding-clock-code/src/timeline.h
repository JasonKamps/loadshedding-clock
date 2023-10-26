#ifndef TIMELINE_H
#define TIMELINE_H

#include "Arduino.h"
#include "Schedule.h"
#include <MD_MAX72xx.h>
#include <SPI.h>

void setupTimeline();
void updateTimeline(Schedule schedule);
void updateTimelineWithEvent(Event event);
void setLED(int index);
void clearTimelineLEDs();
void sweepTimelineLEDs();

#endif