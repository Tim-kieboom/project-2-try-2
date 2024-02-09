#include <Arduino.h>
#include "motor.h"

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

}

void moveMotor(bool motor, uint8_t mode)
{
    /*
        if PIN1 = HIGH & PIN2 = LOW:  motor turns clockwise

        if PIN1 = LOW  & PIN2 = HIGH: motor turns counter_clockwise
    */

    uint8_t motorPin1 = (motor == MOTOR_A) ? MOTOR_A_PIN1 : MOTOR_B_PIN1;
    uint8_t motorPin2 = (motor == MOTOR_A) ? MOTOR_A_PIN2 : MOTOR_B_PIN2;

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

void motorPWM(int cyle_us)
{
    static Timer* timer = new Timer(SET_TIMER_IN_US);

    if(timer->waitTime(cyle_us))
    {
        digitalWrite(ENA, HIGH);
        digitalWrite(ENB, HIGH);
    }
    else
    {
        digitalWrite(ENA, LOW);
        digitalWrite(ENB, LOW);
    }
}

void moveCar(uint8_t mode)
{
    /*
        only if ENA == HIGH: motor_a(A) can move 
        
        only if ENB == HIGH: motor_b(B) can move 


        A(clock wise),            B(clock wise):             forward
        A(counter_clock wise),    B(counter_clock wise):     backwards

        A(clock wise),            B(counter_clock wise):     turn Right
        A(counter_clock wise),    B(clock wise):             turn left
    */

    switch (mode)
    {
        case FORWARD:
            moveMotor(MOTOR_A, CLOCK_WISE); 
            moveMotor(MOTOR_B, CLOCK_WISE); 
            break;
        
        case BACKWARD:
            moveMotor(MOTOR_A, COUNTER_CLOCK_WISE);  
            moveMotor(MOTOR_B, COUNTER_CLOCK_WISE);  
            break;
        
        case LEFT:
            moveMotor(MOTOR_A, COUNTER_CLOCK_WISE);  
            moveMotor(MOTOR_B, CLOCK_WISE);
            break;

        case RIGHT:
            moveMotor(MOTOR_A, CLOCK_WISE); 
            moveMotor(MOTOR_B, COUNTER_CLOCK_WISE); 
            break; 
            
        case STOP_MOVING:
            moveMotor(MOTOR_A, MOTOR_OFF); 
            moveMotor(MOTOR_B, MOTOR_OFF); 

            digitalWrite(ENA, LOW);
            digitalWrite(ENB, LOW);
            return;

    }
}

void testMotor()
{
    moveCar(FORWARD);
    delay(2000);
    moveCar(STOP_MOVING);
    delay(2000);

    moveCar(BACKWARD);
    delay(2000);
    moveCar(STOP_MOVING);
    delay(2000);

    moveCar(LEFT);
    delay(2000);
    moveCar(STOP_MOVING);
    delay(2000);

    moveCar(RIGHT);
    delay(2000);
    moveCar(STOP_MOVING);
    delay(2000);
}

bool moveAndWait_ms(uint8_t move, uint32_t time_ms)
{
    static Timer* timer = new Timer(SET_TIMER_IN_MS);

    moveCar(move);

    bool isTimeOver = timer->waitTime(time_ms);
    delete timer;
    return isTimeOver;
}

bool moveAndWait_ms(uint8_t* moveArray, uint32_t* timeArray_ms)
{
    static int step = 0;
    uint8_t move = BACKWARD;

    if(moveArray[step] == '\0'/*null-asci-value (end of array)*/)
    {  
        step = 0;
        return true;
    }

    move = moveArray[step];

    if(moveAndWait_ms(move, timeArray_ms[step]))
        step++;

    return false;
}