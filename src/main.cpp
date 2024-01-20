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

bool sendData(CarData* data, WifiEsp* wifi)
{
  int* irArray = data->irArray;

  if(irArray[0] == sentinelValue) //if irArray is empty(so start hasn't been pressed yet)
    return wifi->loopWifi();

  return wifi->loopWifi
  (
    data->ulstrasoonData,
    data->REED,
    irArray
  );
}

void setup() 
{
  CarData* data = new CarData();
  WifiEsp* wifi = new WifiEsp();
  init(/*out*/wifi);

  //testMotor();

  while(1)
  {
    data->start = sendData(data, wifi);

    if(!data->start)
      continue;

    carLogic(/*out*/data);
  }

  delete data;
  delete wifi;
}

//void loop() is dumb: made by void setup() enjoyer :) ;) :) ;)
void loop(){}