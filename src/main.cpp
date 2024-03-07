#include <Arduino.h>
#include "CarData.h"
#include "Timer/Timer.h"
#include "myWifi/myWifi.h"
#include "CarLogic/CarLogic.h"
#include "ultrasoon/ultrasoon.h"

void init()
{
  Serial.begin(115200);
  Serial.println("starting");

  //for myWifi to be used you have to upload the html file in the data folder look in the file for more information
  startWifi();

  ultrasoonStartup();
  carLogic_init();
  motorInnit();
  IR_Innit();
}

void sendData(CarData* carData, int carState)
{
  static int ultrasoonBuffer = 0;
  int ultrasoon = 0;

  if(carData->ulstrasoonData != READING_NOT_FOUND)
    ultrasoon = carData->ulstrasoonData;
  else
    ultrasoonBuffer++;
  
  if(ultrasoonBuffer >= 10)
  {
    ultrasoon = -1;
    ultrasoonBuffer = 0;
  }

  setSensorData_In_Json
  (
    getStringState(carState), 
    ultrasoon, 
    carData->irArray, 
    carData->REED
  );
}

void setup() 
{

  CarData* carData = new CarData();
  int carState = driveForward;

  init();
  sendData(carData, carState);

   while(1)
   {
     if(carState == end)
       break;

     bool wifiStart = getWifiState(); 

     Serial.println("state: " + String(wifiStart));

     if(!wifiStart)
     {  
       moveCar(STOP_MOVING);
       setSensorData_toEmpty();
       continue;
     }

     carLogic(/*out*/carData, /*out*/carState);
     sendData(carData, carState);

     Serial.println(carState);
  }

  Serial.println("ending program");

  delete carData;
}


void loop(){moveCar(FORWARD);}
