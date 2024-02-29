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

  ~CarData()
  {
    if(irArray != nullptr)
      delete irArray;
  }

  //ir = infraRed sensor used to follow the line of the maze
  int* irArray;
  
  //megnatic sensor used to sens the end of the maze
  bool REED = false;

  //can sens object so the car can avoid them
  int ulstrasoonData = 0;
};

#endif