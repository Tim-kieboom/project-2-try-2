#ifndef _IR_SENSOR_H_
#define _IR_SENSOR_H_

#define CALULATE_DISTANCE(outputSensor) (int)( (double)outputSensor * 0.01715 )

#define READING_NOT_FOUND INT16_MIN
#define TRIGGER_PIN 17
#define ECHO_PIN 16

#define SET_TIMER_IN_MS TRUE
#define SET_TIMER_IN_US false


#include "Timer/Timer.h"

void ultrasoonStartup();
int readUltrasoon();
bool soon_Detect(int distance);

#endif