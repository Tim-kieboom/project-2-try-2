#include <Arduino.h>
#include "CarData.h"
#include "Timer/Timer.h"
#include "wifi/wifiEsp.h"
#include "CarLogic/CarLogic.h"

void init(WifiEsp* wifi)
{
  Serial.begin(115200);
  Serial.println("starting");

  wifi->wifi_Innit();

  pinMode(REED_PIN, OUTPUT);
  ultrasoonStartup();
  IR_Innit();
  motorInnit();
}

bool sendData(CarData* carData, WifiEsp* wifi)
{
  int* irArray = carData->irArray;

  if(irArray[0] == SENTINEL_VALUE) //if irArray is empty(so start hasn't been pressed yet)
    return wifi->loopWifi();

  return wifi->loopWifi
  (
    carData->ulstrasoonData,
    carData->REED,
    irArray
  );
}

void setup() 
{
  CarData* carData = new CarData();
  WifiEsp* wifi = new WifiEsp();
  init(/*out*/wifi);

  bool start = false;

  while(1){testMotor();}

  while(1)
  {

    int wifiState = sendData(carData, wifi);
    
    if(wifiState == START)
      start = true;

    if(wifiState == STOP) 
      break;

    if(!start)
      continue;

    carLogic(/*out*/carData);
  }

  delete carData;
  delete wifi;
}

void loop(){}
