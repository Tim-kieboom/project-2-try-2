#include "mainHeader.h"

struct CarData
{
  bool start = false;
  int irData1 = 0;
  int irData2 = 0;
  int ulstrasoonData = 0;
};

int main() 
{
  bool start = false;
  int irData1 = 0;
  int irData2 = 0;
  int ulstrasoonData = 0;

  WifiEsp* wifi = new WifiEsp();
  wifi->wifi_Innit();

  while(1)
  {
    if(start)
    {

    }
    else
    {
      move(STOP_MOVING);
    }

    wifi->loopWifi(irData1, irData2, ulstrasoonData);
  }

  delete wifi;
  return 0;
}