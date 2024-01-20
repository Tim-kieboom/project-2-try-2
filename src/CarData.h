#pragma once
#ifndef CARDATA_H
#define CARDATA_H

#include <cstdint>

#define sentinelValue -1

struct CarData
{
  CarData()
  {
    irArray = new int[1];
    
    //the sentinelValue is to notify the person using this struct that the array is empty
    irArray[0] = sentinelValue; 
  }

  int* irArray;
  bool REED = false;
  bool start = false;
  int ulstrasoonData = 0;
};

#endif