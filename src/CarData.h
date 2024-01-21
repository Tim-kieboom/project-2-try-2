#pragma once
#ifndef CARDATA_H
#define CARDATA_H

#include <cstdint>
#include "IR_sensor/IR_sensor.h"

struct CarData
{
  CarData()
  {
    irArray = new int[1];
    
    //the sentinelValue is to notify the person using this struct that the array is empty
    irArray[0] = SENTINEL_VALUE; 
  }

  int* irArray;
  bool REED = false;
  int ulstrasoonData = 0;
};

#endif