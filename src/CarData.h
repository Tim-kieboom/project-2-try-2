#pragma once
#ifndef CARDATA_H
#define CARDATA_H

#include <cstdint>

class CarData
{
public:
  bool start = false;
  uint8_t irData1 = 0;
  uint8_t irData2 = 0;
  int ulstrasoonData = 0;
};

#endif