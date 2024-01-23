#include "debug.h"

void printUltrasoon(bool print)
{
  int distance = readUltrasoon_cm();

  if(distance == READING_NOT_FOUND)
    return;

    Serial.print("ultrasoon: ");
    Serial.print(distance);
    Serial.println("cm");
}

void debugUltrasoon(int time_ms)
{
  static Timer timer = Timer(SET_TIMER_IN_MS);
  
  if(timer.waitTime(time_ms))
  {
    printUltrasoon();
  }

}

void debugIR(int time_ms)
{
  static Timer timer = Timer(SET_TIMER_IN_MS);

  if(timer.waitTime(time_ms))
  {
    printIR_Data();
  }
}

void debugSensors(int time_ms)
{
  static Timer timer = Timer(SET_TIMER_IN_MS);
  bool print = false;

  if(timer.waitTime(time_ms))
  {  
    print = true;
    printIR_Data();
    Serial.println();
  }

    printUltrasoon(print);
}