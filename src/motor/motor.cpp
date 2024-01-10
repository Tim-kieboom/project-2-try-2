#include <Arduino.h>
#include "motor.h"

//PIN1 HIGH, PIN2 LOW: turn motor clockwise(clw)
//PIN2 HIGH, PIN1 LOW: turn motor counter_clockwise(c_clw)

//A(clock wise),            B(clock wise):             forward
//A(counter_clock wise),    B(counter_clock wise):     backwards

//A(clock wise),            B(counter_clock wise):     turn Right
//A(counter_clock wise),    B(clock wise):             turn left

static const int frequency = 500;
static const int resolution = 8;
static const uint8_t channel_A = 0;
static const uint8_t channel_B = 1;


void motorInnit()
{
    pinMode(MOTOR_A_PIN1, OUTPUT);
    pinMode(MOTOR_A_PIN2, OUTPUT);

    pinMode(MOTOR_B_PIN1, OUTPUT);
    pinMode(MOTOR_B_PIN2, OUTPUT);

    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);

    ledcAttachPin(ENA, channel_A);
    ledcSetup(channel_A, frequency, resolution);
    ledcAttachPin(ENB, channel_B);
    ledcSetup(channel_B, frequency, resolution);
}

void moveMotor(uint8_t motorPin1, uint8_t motorPin2, uint8_t mode)
{
    switch (mode)
    {
        case CLOCK_WISE:
            digitalWrite(motorPin1, HIGH);
            digitalWrite(motorPin2, LOW);
            break;

        case COUNTER_CLOCK_WISE:
            digitalWrite(motorPin1, LOW);
            digitalWrite(motorPin2, HIGH);
            break;
        
        case MOTOR_OFF:
            digitalWrite(motorPin1, LOW);
            digitalWrite(motorPin2, LOW);
            break;

        default:
            break;
    }
}

void moveCar(uint8_t mode, int speed)
{

    switch (mode)
    {
        case FORWARD:
            moveMotor(MOTOR_A_PIN1, MOTOR_A_PIN2, CLOCK_WISE); 
              
            moveMotor(MOTOR_B_PIN1, MOTOR_B_PIN2, CLOCK_WISE); 

            ledcWrite(channel_A,(255*speed));
            ledcWrite(channel_B,(255*speed));
            break;
        
        case BACKWARD:
            moveMotor(MOTOR_A_PIN1, MOTOR_A_PIN2, COUNTER_CLOCK_WISE);  

            moveMotor(MOTOR_B_PIN1, MOTOR_B_PIN2, COUNTER_CLOCK_WISE); 

            ledcWrite(channel_A,(255*speed));
            ledcWrite(channel_B,(255*speed));     
            break;
        
        case TURN_LEFT:
            moveMotor(MOTOR_A_PIN1, MOTOR_A_PIN2, COUNTER_CLOCK_WISE);  

            moveMotor(MOTOR_B_PIN1, MOTOR_B_PIN2, CLOCK_WISE);

            ledcWrite(channel_A,(255*speed));
            ledcWrite(channel_B,(255*speed));  
            break;

        case TURN_RIGHT:
            moveMotor(MOTOR_A_PIN1, MOTOR_A_PIN2, CLOCK_WISE); 

            moveMotor(MOTOR_B_PIN1, MOTOR_B_PIN2, COUNTER_CLOCK_WISE); 

            ledcWrite(channel_A,(255*speed));
            ledcWrite(channel_B,(255*speed));
            break; 
            
        case STOP_MOVING:
            moveMotor(MOTOR_A_PIN1, MOTOR_A_PIN2, MOTOR_OFF); 
   
            moveMotor(MOTOR_B_PIN1, MOTOR_B_PIN2, MOTOR_OFF); 
  
            ledcWrite(channel_A,(0));
            ledcWrite(channel_B,(0));
            break;

    }
}

void testMotor()
{
    moveCar(FORWARD, 1);
    delay(2000);
    moveCar(STOP_MOVING, 0);
    delay(2000);

    moveCar(BACKWARD, 1);
    delay(2000);
    moveCar(STOP_MOVING, 0);
    delay(2000);

    moveCar(TURN_LEFT, 1);
    delay(2000);
    moveCar(STOP_MOVING, 0);
    delay(2000);

    moveCar(TURN_RIGHT, 1);
    delay(2000);
    moveCar(STOP_MOVING,0);
    delay(2000);
}


