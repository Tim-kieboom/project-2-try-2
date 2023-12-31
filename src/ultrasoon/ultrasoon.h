#pragma once
#ifndef ULTRASOON_H
#define ULTRASOON_H

#define CALULATE_DISTANCE(outputSensor) (int)( (double)outputSensor * 0.01715 )

#define READING_NOT_FOUND -69
#define TRIGGER_PIN 17
#define ECHO_PIN 16

#define SET_TIMER_IN_MS TRUE
#define SET_TIMER_IN_US false

#include "Timer/Timer.h"

enum ultrasoonMode
{
  begin = 0,
  sendSound = 1,
  readTheDistance = 2,
  reset = 3
};

void ultrasoonStartup();
int readUltrasoon();
bool soon_Detect(int distance);

#endif