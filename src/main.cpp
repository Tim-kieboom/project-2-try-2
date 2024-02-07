#include <Arduino.h>
#include "CarData.h"
#include "Timer/Timer.h"
#include "myWifi/myWifi.h"
#include "CarLogic/CarLogic.h"

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
  setSensorData_In_Json
  (
    getStringState(carState), 
    carData->ulstrasoonData, 
    carData->irArray, 
    carData->REED
  );
}

void setup() 
{
  Timer* dataSendTimer = new Timer(SET_TIMER_IN_MS);
  CarData* carData = new CarData();
  int carState = driveForward;

  init();

  sendData(carData, carState);

  while(1)
  {
    if(carState == end)
      break;

    //wifiState={idle, start, stop}
    bool wifiStart = getWifiState(); 

    if(!wifiStart)
      continue;

    carLogic(/*out*/carData, /*out*/carState);

    sendData(carData, carState);
  }

  Serial.println("ending program");

  delete carData;
  delete dataSendTimer;
}


void loop(){}
