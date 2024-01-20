#pragma once
#ifndef CARDATA_H
#define CARDATA_H

#include <cstdint>

struct CarData
{
  bool start = false;
  int* irArray;
  int ulstrasoonData = 0;
  bool REED = false;
};

#endif