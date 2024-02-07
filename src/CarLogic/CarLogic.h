#pragma once
#ifndef _CARLOGIC_H_
#define _CARLOGIC_H_

#define REED_PIN 18

#include "./CarData.h"
#include "motor/motor.h"
#include "Timer/Timer.h"
#include "IR_sensor/IR_Sensor.h"
#include "ultrasoon/ultrasoon.h"

enum CarState
{
  driveForward,
  lineAtBack,
  lineAtLeft,
  lineAtRight,
  lineAtFrontFirst,
  lineAtFrontSecond,
  lineAtBothSides,
  detectedObstacle,
  end
};

void carLogic_init();
void printState(int carState);
String getStringState(int carState);
void carLogic(CarData* data,int &carState);

#endif