#include "CarLogic.h"

enum CarState
{
  driveForward,
  lineAtBack,
  lineAtLeft,
  lineAtRight,
  lineAtFrontFirst,
  lineAtFrontSecond,
  detectedObstacle,
  end
};

bool moveAndWait_ms(int mode , int time_ms)
{
  static Timer* timer = NULL;

  if(timer == NULL)
    timer = new Timer(SET_TIMER_IN_MS);

  moveCar(mode);
  
  if(timer->waitTime(time_ms))
  {  
    delete timer;
    return true;
  }

  return false;
}

bool backAndRight()
{
  static int step = 0;
  static int move = BACKWARD;

  if(moveAndWait_ms(BACKWARD, 20/*ms*/))
    step++;

  switch(step)
  {
    case 0:
      move = BACKWARD;
      break;

    case 1:
      move = RIGHT;
      break;

    case 2: //reset
      move = BACKWARD;
      step = 0;
      return true;
  }

  return false;
}

void carDoesState(int &carState)
{
  static bool isDone       = false;
  static bool isDoneSecond = false;

  switch(carState)
  {
    case driveForward: //go forward
      moveCar(FORWARD);
      break;

    case lineAtBack: //go forward
      carState = driveForward;
      break;

    case lineAtRight: //go left
      if(moveAndWait_ms(LEFT, 20/*ms*/))
        carState = driveForward;
      break;

    case lineAtLeft: //go right
      if(moveAndWait_ms(RIGHT, 20/*ms*/))
        carState = driveForward;
      break;

    case lineAtFrontFirst: //go back and then right
      isDone = backAndRight();

      if(isDone)
      {  
        carState = driveForward;
        isDone = false;
      }
      break;

    case lineAtFrontSecond: //go back, right and then left
      isDone = backAndRight();
      
      if(isDoneSecond)
      {
        carState = driveForward;
        isDoneSecond = false;
      }
      
      if(isDone)
      {  
        isDoneSecond = moveAndWait_ms(LEFT, 20/*ms*/);
        isDone = false;
      }

      break;

    case end: //stop moveing
      moveCar(STOP_MOVING);
      break;
  }
}

void checkIR_Sensors(int* IRs, int &carState)
{
  if(IRs[BACKWARD]     > 0)
    carState = lineAtBack;

  else if(IRs[RIGHT]   > 0)
    carState = lineAtRight;

  else if(IRs[LEFT]    > 0)
    carState = lineAtLeft;

  else if(IRs[FORWARD] > 0)
  { 
    if(carState == lineAtFrontFirst)  
      carState = lineAtFrontSecond;

    carState = lineAtFrontFirst;
  }
}

void getSensorData(CarData* carData)
{ 
  int* oldIRs   = carData->irArray;

  carData->REED           = digitalRead(REED_PIN);
  carData->irArray        = checkIR();
  carData->ulstrasoonData = readUltrasoon_cm();

  delete[] oldIRs;
}

void carLogic(CarData* carData)
{
  static int carState = driveForward;

  getSensorData(/*out*/carData);

  checkIR_Sensors(carData->irArray, /*out*/carState);

  if(ultrasoonDetectAtDistance_cm(20))
    carState = detectedObstacle;
  
  //zie aan bijde zijkanten zwarte lijn????

  if(carData->REED)
    carState = end;

  carDoesState(/*out*/carState);
}