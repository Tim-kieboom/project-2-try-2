#include "Arduino.h"
#include "ultrasoon.h"

static int readDistance = 0;


void ultrasoonStartup()
{
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

int readUltrasoon()
{
  static Timer timer_us = Timer(SET_TIMER_IN_US);
  timer_us.startTimer();

  static int step = 0;
  static ultrasoonMode mode = begin;

  if( timer_us.waitTime(1) )
  {
    step++;
    timer_us.resetBeginTime();
  }

  switch (mode)
  {
    case begin:
      digitalWrite(TRIGGER_PIN, LOW);
      mode = sendSound;
      break;
    
    case sendSound:
      if(step >= 2)
      {
        digitalWrite(TRIGGER_PIN, HIGH);
        mode = readTheDistance;
      }
      break;
    
    case readTheDistance:
      if(step >= 10)
      {
        digitalWrite(TRIGGER_PIN, LOW);
        mode = reset;

        int sensorOutput = pulseIn(ECHO_PIN, HIGH);
        int distance = CALULATE_DISTANCE(sensorOutput);

        return distance;
      }
      break;

    case reset:
      step = 0;
      mode = begin;
      break;

    default:
      break;
  }

  return READING_NOT_FOUND;
}

bool soon_Detect(int distance)
{
  static int timer = 0;
  static int safetyBuffer = 0;
  int newDistance = readUltrasoon();

  if(newDistance == READING_NOT_FOUND)
    return false;


  if(newDistance != 0)
    readDistance = newDistance;
  
  timer++;

  if(newDistance <= distance && readDistance != 0)
  {
    safetyBuffer++;
  }
  else if(timer >= 10)
  {
    timer = 0;
    safetyBuffer = 0;
  }

  if(safetyBuffer >= 4)
  {
    safetyBuffer = 0;
    return true;
  }

  return false;
}