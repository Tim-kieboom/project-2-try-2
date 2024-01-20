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
  static Timer* timer = new Timer(SET_TIMER_IN_MS);
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

void carDoesState(CarState &carState)
{
  bool isDone       = false;
  bool isDoneSecond = false;

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
        carState = driveForward;
      break;

    case lineAtFrontSecond: //go back, right and then left
      isDone       = backAndRight();
      isDoneSecond = false;

      if(isDone)
        isDoneSecond = moveAndWait_ms(LEFT, 20/*ms*/);

      if(isDoneSecond)
        carState = driveForward;
      break;

    case end: //stop moveing
      moveCar(STOP_MOVING);
      break;
  }
}

void checkIR_Sensors(int* IRs, CarState &carState)
{
  if(IRs[BACKWARD] > 0)
    carState = lineAtBack;

  else if(IRs[RIGHT] > 0)
    carState = lineAtRight;

  else if(IRs[LEFT] > 0)
    carState = lineAtLeft;

  else if(IRs[FORWARD] > 0)
  { 
    if(carState == lineAtFrontFirst)  
      carState = lineAtFrontSecond;

    carState = lineAtFrontFirst;
  }
}

void getSensorData(CarData* data)
{ 
  int* oldIRs   = data->irArray;

  data->REED           = digitalRead(REED_PIN);
  data->irArray        = checkIR();
  data->ulstrasoonData = readUltrasoon();

  delete[] oldIRs;
}

void carLogic(CarData* data)
{
  static CarState carState = driveForward;

  getSensorData(/*out*/data);

  checkIR_Sensors(data->irArray, /*out*/carState);

  if(ultrasoonDetectAtDistance(20/*cm*/))
    carState = detectedObstacle;
  
  //zie aan bijde zijkanten zwarte lijn????

  if(data->REED)
    carState = end;

  carDoesState(/*out*/carState);
}