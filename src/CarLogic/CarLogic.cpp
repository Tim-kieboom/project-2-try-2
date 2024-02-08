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

void carDoesState(int &carState)
{
  uint8_t*  moveArray   = nullptr;
  uint32_t* moveTime_ms = nullptr;

  switch(carState) 
  {
    case driveForward: //go forward
      moveCar(FORWARD);
      motorPWM(80/*us pulse freq*/);
      return;

    case lineAtBack: //go forward
      carState = driveForward;
      digitalWrite(ENA, HIGH);
      digitalWrite(ENB, HIGH);
      return;

    case lineAtRight: //go back and left
      moveArray    = new uint8_t[2] {BACKWARD, LEFT}; 
      moveTime_ms  = new uint32_t[2]{300,      1200}; 
      break;

    case lineAtLeft: //go back and right
      moveArray    = new uint8_t[2] {BACKWARD, RIGHT}; 
      moveTime_ms  = new uint32_t[2]{300,      1200};
      break;

    case lineAtFrontFirst: //go back and then right
      moveArray    = new uint8_t[2] {BACKWARD, RIGHT}; 
      moveTime_ms  = new uint32_t[2]{600,      1600};
      break;

    case lineAtFrontSecond: //go back, right and then left
      moveArray    = new uint8_t[3] {BACKWARD, RIGHT, LEFT};
      moveTime_ms  = new uint32_t[3]{600,      1600,  1600};
      break;

    case lineAtBothSides: //go back and then left
      moveArray    = new uint8_t[2] {BACKWARD, LEFT};
      moveTime_ms  = new uint32_t[2]{800,      800};
      break;

    case detectedObstacle: //avoid obstikal
      moveArray    = new uint8_t[2] {BACKWARD, RIGHT};
      moveTime_ms  = new uint32_t[2]{600,      1600};
      break;

    case end: //stop moveing
      moveCar(STOP_MOVING);
      return;
  }

  if(moveAndWait_ms(moveArray, moveTime_ms))
    carState = driveForward;

  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);

  if (moveArray != nullptr)
    delete[] moveArray;
  if (moveTime_ms != nullptr)
    delete[] moveTime_ms;
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