#include "CarLogic.h"

//if (ultrasoon <= 15cm)
#define OBSTACLE_IS_SEEN ultrasoonDetectAtDistance_cm(15)


void carLogic_init()
{
  pinMode(REED_PIN, INPUT);
}

String getStringState(int carState)
{
  switch (carState) 
  {
  case driveForward:
    return "driveForward";
    break;

  case lineAtBack:
    return "lineAtBack";
    break;
  
  case lineAtLeft:
    return "lineAtLeft";
    break;

  case lineAtRight:
    return "lineAtRight";
    break;

  case lineAtFrontFirst:
    return "lineAtFrontFirst";
    break;

  case lineAtFrontSecond:
    return "lineAtFrontSecond";
    break;

  case lineAtBothSides:
    return "lineAtBothSides";
    break;

  case detectedObstacle:
    return "detectedObstacle";
    break;

  case end:
    return "end";
    break;
  
  default:
    break;
  }
  return "no state";
}

void printState(int carState)
{
  Serial.println(getStringState(carState));
}


// bool moveAndWait_ms(uint8_t* moveArray, uint32_t* timeArray_ms)
// {
//   static int step = 0;
//   static uint8_t move = moveArray[0];

//   //if end of moveArray is reached reset funtion
//   if(step > sizeof(moveArray))
//   {  
//     step = 0;
//     return true;
//   }

//   move = moveArray[step];

//   if(moveAndWait_ms(move, timeArray_ms[step]/*ms*/))
//     step++;

//   return false;
// }

bool moveAndWait_ms(uint8_t mode , uint32_t time_ms)
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

bool backAndLeft(uint32_t* time_ms)
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
      move = LEFT;
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

  uint32_t moveTime[3] = {0,0,0};

  switch(carState) 
  {
    case driveForward: //go forward
      moveCar(FORWARD);
      //motorPWM(500/*ms pulse freq*/);
      break;

    case lineAtBack: //go forward
      moveCar(FORWARD);
      //motorPWM(500/*ms pulse freq*/);
      break;

    case lineAtRight: //go left
      moveTime[0/*backward*/] = 300/*ms*/;
      moveTime[1/*left*/]     = 400/*ms*/;

      if(moveBackAnd(RIGHT, moveTime/*ms*/))
      carState = driveForward;
      break;

    case lineAtLeft: //go right
      moveTime[0/*backward*/] = 300/*ms*/;
      moveTime[1/*right*/]    = 400/*ms*/;

      if(moveBackAnd(LEFT, moveTime/*ms*/))
        carState = driveForward;
      break;

    case lineAtFrontFirst: //go back and then right
      moveTime[0/*backward*/] = 600/*ms*/;
      moveTime[1/*right*/]    = 500/*ms*/;
      
      isDone = backAndRight(moveTime/*ms*/);

      if(isDone)
      {  
        carState = driveForward;
        isDone = false;
      }
      break;

    case lineAtFrontSecond: //go back, right and then left
      moveTime[0/*backward*/] = 600/*ms*/;
      moveTime[1/*right*/]    = 500/*ms*/;
      moveTime[2/*left*/]     = 500/*ms*/;

      carState = lineAtFrontFirst; 
      break;

      if(backAndRightAnd(LEFT, moveTime/*ms*/))
        carState = driveForward;
      break;

    case lineAtBothSides:    
      isDone = moveAndWait_ms(BACKWARD, 500/*ms*/);

      if(isDoneSecond)
      {
        carState = driveForward;
        isDoneSecond = false;
      }
      
      if(isDone)
      {  
        isDoneSecond = moveAndWait_ms(LEFT, 500/*ms*/);
        isDone = false;
      }
      break;

    case detectedObstacle: //avoid obstikal(back and then right)
      moveTime[0/*backward*/] = 600/*ms*/;
      moveTime[1/*right*/]    = 800/*ms*/;

      isDone = backAndLeft(moveTime/*ms*/);

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

  bool isForward   = IRs[0] > 0;
  bool isBackward  = IRs[1] > 0;
  bool isLeft      = IRs[2] > 0;
  bool isRight     = IRs[3] > 0;

  if(isBackward)
    carState = lineAtBack;

  else if(isLeft && isRight)
    carState = lineAtBothSides;

  else if(isRight)
    carState = lineAtRight;

  else if(isLeft)
    carState = lineAtLeft;

  else if(isForward)
  { 
    if(carState == lineAtFrontFirst && timer->waitTime(500/*ms*/))  
    {
      isSecondFront = true;
    }

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

  if(OBSTACLE_IS_SEEN)
    carState = detectedObstacle;

  checkIR_Sensors(carData->irArray, /*out*/carState);

  if(carData->REED)
    carState = end;

  carDoesState(/*out*/carState);
}