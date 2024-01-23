#include "CarLogic.h"

#define OBSTACLE_IS_SEEN ultrasoonDetectAtDistance_cm(15/*cm*/)


void carLogic_init()
{
  pinMode(REED_PIN, INPUT);
}

void printState(int carState)
{
  switch (carState) 
  {
  case driveForward:
    Serial.println("driveForward");
    break;

  case lineAtBack:
    Serial.println("lineAtBack");
    break;
  
  case lineAtLeft:
    Serial.println("lineAtLeft");
    break;

  case lineAtRight:
    Serial.println("lineAtRight");
    break;

  case lineAtFrontFirst:
    Serial.println("lineAtFrontFirst");
    break;

  case lineAtFrontSecond:
    Serial.println("lineAtFrontSecond");
    break;

  case lineAtBothSides:
    Serial.println("lineAtBothSides");
    break;

  case detectedObstacle:
    Serial.println("detectedObstacle");
    break;

  case end:
    Serial.println("end");
    break;
  
  default:
    break;
  }
}

bool moveAndWait_ms(int mode , uint32_t time_ms)
{
  static Timer* timer = new Timer(SET_TIMER_IN_MS);

  moveCar(mode);
  
  if(timer->waitTime(time_ms))
  {  
    return true;
  }

  return false;
}

bool backAndRight(uint32_t* time_ms)
{
  static int step = 0;
  static int move = BACKWARD;

  if(moveAndWait_ms(move, time_ms[step]/*ms*/))
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

bool backAndRightAnd(int mode, uint32_t* time_ms)
{
  static int step = 0;
  static int move = BACKWARD;

  if(moveAndWait_ms(move, time_ms[step]/*ms*/))
    step++;

  switch(step)
  {
    case 0:
      move = BACKWARD;
      break;

    case 1:
      move = RIGHT;
      break;

    case 2:
      move = mode;
      break;

    case 3: //reset
      move = BACKWARD;
      step = 0;
      return true;
  }

  return false;
}

bool moveBackAnd(int mode, uint32_t* time_ms)
{
  static int step = 0;
  static int move = BACKWARD;

  if(moveAndWait_ms(move, time_ms[step]/*ms*/))
    step++;

  switch(step)
  {
    case 0:
      move = BACKWARD;
      break;

    case 1:
      move = mode;
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

  const uint32_t moveTime[] = {1000/*Back_ms*/, 1800/*turn1_ms*/, 1800/*turn2_ms*/};

  switch(carState)
  {
    case driveForward: //go forward
      moveCar(FORWARD);
      motorPWM(80/*us pulse freq*/);
      return;

    case lineAtBack: //go forward
      carState = driveForward;
      break;

    case lineAtRight: //go left
      if(moveBackAnd(RIGHT, moveTime/*ms*/))
        carState = driveForward;
      break;

    case lineAtLeft: //go right
      if(moveBackAnd(LEFT, moveTime/*ms*/))
        carState = driveForward;
      break;

    case lineAtFrontFirst: //go back and then right
      
      isDone = backAndRight(moveTime/*ms*/);

      if(isDone)
      {  
        carState = driveForward;
        isDone = false;
      }
      break;

    case lineAtFrontSecond: //go back, right and then left
      carState = lineAtFrontFirst; 
      break;

      if(backAndRightAnd(LEFT, moveTime/*ms*/))
        carState = driveForward;
      break;

    case lineAtBothSides:
      isDone = moveAndWait_ms(BACKWARD, 800/*ms*/);

      if(isDoneSecond)
      {
        carState = driveForward;
        isDoneSecond = false;
      }
      
      if(isDone)
      {  
        isDoneSecond = moveAndWait_ms(LEFT, 800/*ms*/);
        isDone = false;
      }
      break;

    case detectedObstacle: //avoid obstikal
      isDone = backAndRight(moveTime/*ms*/);

      if(isDone && !OBSTACLE_IS_SEEN)
        carState = driveForward;
      break;

    case end: //stop moveing
      moveCar(STOP_MOVING);
      return;

    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
  }
}

void checkIR_Sensors(int* IRs, int &carState)
{
  static Timer* timer = new Timer(SET_TIMER_IN_MS);
  static bool isSecondFront = false;

  if(IRs[BACKWARD]     > 0)
    carState = lineAtBack;

  else if(IRs[LEFT] > 0 && IRs[RIGHT] > 0)
    carState = lineAtBothSides;

  else if(IRs[RIGHT]   > 0)
    carState = lineAtRight;

  else if(IRs[LEFT]    > 0)
    carState = lineAtLeft;

  else if(IRs[FORWARD] > 0)
  { 
    if(carState == lineAtFrontFirst && timer->waitTime(500))  
      isSecondFront = true;

    if(isSecondFront)  
    {  
      carState = lineAtFrontSecond;
      return;
    }

    carState = lineAtFrontFirst;
    return;
  }

  timer->resetBeginTime();
  isSecondFront = false;
}

void getSensorData(CarData* carData)
{ 
  int* oldIRs   = carData->irArray;

  carData->REED           = !digitalRead(REED_PIN);
  carData->irArray        = checkIR();
  carData->ulstrasoonData = readUltrasoon_cm();

  delete[] oldIRs;
}

void carLogic(CarData* carData, int &carState)
{
  //default state is driveForward

  getSensorData(/*out*/carData);

  checkIR_Sensors(carData->irArray, /*out*/carState);

  if(OBSTACLE_IS_SEEN)
    carState = detectedObstacle;

  if(carData->REED)
    carState = end;

  carDoesState(/*out*/carState);
}