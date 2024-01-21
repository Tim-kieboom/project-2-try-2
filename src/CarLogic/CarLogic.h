#pragma once
#ifndef _CARLOGIC_H_
#define _CARLOGIC_H_

#define REED_PIN 18

#include "./CarData.h"
#include "motor/motor.h"
#include "Timer/Timer.h"
#include "IR_sensor/IR_Sensor.h"
#include "ultrasoon/ultrasoon.h"

void carLogic(CarData* data);

#endif