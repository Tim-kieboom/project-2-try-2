#include "Arduino.h"
#include "ultrasoon.h"

static int readDistance = 0;


void ultrasoonStartup()
{
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

int readUltrasoon_cm()
{
  static Timer* timer_us = new Timer(SET_TIMER_IN_US);

  static int step = 0;
  static int mode = begin;

  if( timer_us->waitTime(1) )
    step++;

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

        int sensorOutput = pulseIn(ECHO_PIN, HIGH);
        int distance = CALULATE_DISTANCE(sensorOutput);

        mode = reset;
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

bool ultrasoonDetectAtDistance_cm(int distance_cm)
{
  static int timer = 0;
  static int safetyBuffer = 0;
  int newDistance = readUltrasoon_cm();

  if(newDistance == READING_NOT_FOUND)
    return false;


  if(newDistance != 0)
    readDistance = newDistance;
  
  timer++;

  if(newDistance <= distance_cm && readDistance != 0)
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