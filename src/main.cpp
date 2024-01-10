#include "mainHeader.h"

struct CarData
{
  bool start = false;
  uint8_t irData1 = 0;
  uint8_t irData2 = 0;
  int ulstrasoonData = 0;
};

void init()
{
  Serial.begin(115200);
  Serial.println("starting");

  ultrasoonStartup();
  IR_Innit();
}

void printUltrasoon()
{
  static Timer timer = Timer(SET_TIMER_IN_MS);
  timer.updateTimer();
  
  if(timer.waitTime(200))
  {
    Serial.println(readUltrasoon());
    timer.resetBeginTime();
  }
}

void printIR_Sensors()
{
  static Timer timer = Timer(SET_TIMER_IN_MS);
  timer.updateTimer();

  if(timer.waitTime(200))
  {
    printIR_Data();
    timer.resetBeginTime();
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

void carLogic(CarData* data)
{
  if(data->start)
  {

  }
  else
  {
    moveCar(STOP_MOVING, 0);
  }
}

void setup() 
{
  CarData* data = new CarData();
  WifiEsp* wifi = new WifiEsp();
  wifi->wifi_Innit();
  init();

  testMotor();

  while(1)
  {
    carLogic(data);

    data->start = wifi->loopWifi
    (
      data->irData1, 
      data->irData2, 
      data->ulstrasoonData
    );
  }

  delete data;
  delete wifi;
}

void loop(){}