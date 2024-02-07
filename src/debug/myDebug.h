#pragma once
#ifndef _MYDEBUG_H_
#define _MYDEBUG_H_

#include "./Timer/Timer.h"
#include "./IR_sensor/IR_Sensor.h"
#include "./ultrasoon/ultrasoon.h"

void printUltrasoon();
void debugIR(int time_ms);
void debugSensors(int time_ms);


#endif