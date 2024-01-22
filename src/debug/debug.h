#pragma once
#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "./Timer/Timer.h"
#include "./IR_sensor/IR_Sensor.h"
#include "./ultrasoon/ultrasoon.h"

void debugSensors(int time_ms);
void printUltrasoon();
void debugIR(int time_ms);


#endif