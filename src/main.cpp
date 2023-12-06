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
  ultrasoonStartup();
  IR_Innit();
}

void carLogic(CarData* data)
{
  if(data->start)
  {

  }
  else
  {
    move(STOP_MOVING);
  }
}

int main() 
{
  CarData* data = new CarData();
  WifiEsp* wifi = new WifiEsp();
  wifi->wifi_Innit();
  init();
  
  while(1)
  {
    carLogic(data);

    data->start = wifi->loopWifi(data->irData1, data->irData2, data->ulstrasoonData);
  }

  delete data;
  delete wifi;
  return 0;
}