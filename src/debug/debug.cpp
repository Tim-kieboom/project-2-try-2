#include "debug.h"

void printUltrasoon()
{
  static Timer timer = Timer(SET_TIMER_IN_MS);
  
  if(timer.waitTime(200))
  {
    Serial.println(readUltrasoon());
  }
}

void printIR_Sensors()
{
  static Timer timer = Timer(SET_TIMER_IN_MS);

  if(timer.waitTime(200))
  {
    printIR_Data();
  }
}

void debugSensors()
{
  while(1)
  {
    printUltrasoon();
    printIR_Data();
  }
}