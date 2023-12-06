#include <Arduino.h>
#include "motor.h"

//PIN1 HIGH: turn motor clockwise(clw)
//PIN2 HIGH: turn motor counter_clockwise(c_clw)

//A(clock wise), B(clock wise):                     forward
//A(counter_clock wise), B(counter_clock wise):     backwards

//A(clock wise), B(counter_clock wise):             turn Right
//A(counter_clock wise), B(clock wise):             turn left

void motorInnit()
{
    pinMode(MOTOR_A_PIN1, OUTPUT);
    pinMode(MOTOR_A_PIN2, OUTPUT);

    pinMode(MOTOR_B_PIN1, OUTPUT);
    pinMode(MOTOR_B_PIN2, OUTPUT);
}

void move(int mode)
{

    switch (mode)
    {
        case FORWARD:
            digitalWrite(MOTOR_A_PIN1, HIGH);    
            digitalWrite(MOTOR_A_PIN2, LOW);    
            digitalWrite(MOTOR_B_PIN1, HIGH);    
            digitalWrite(MOTOR_B_PIN2, LOW);   
            break;
        
        case BACKWARD:
            digitalWrite(MOTOR_A_PIN1, LOW);    
            digitalWrite(MOTOR_A_PIN2, HIGH);    
            digitalWrite(MOTOR_B_PIN1, LOW);    
            digitalWrite(MOTOR_B_PIN2, HIGH);     
            break;
        
        case TURN_LEFT:
            digitalWrite(MOTOR_A_PIN1, HIGH);    
            digitalWrite(MOTOR_A_PIN2, LOW);    
            digitalWrite(MOTOR_B_PIN1, LOW);    
            digitalWrite(MOTOR_B_PIN2, HIGH);     
            break;

        case TURN_RIGHT:
            digitalWrite(MOTOR_A_PIN1, LOW);    
            digitalWrite(MOTOR_A_PIN2, HIGH);    
            digitalWrite(MOTOR_B_PIN1, HIGH);    
            digitalWrite(MOTOR_B_PIN2, LOW);   
            break; 
            
        case STOP_MOVING:
            digitalWrite(MOTOR_A_PIN1, LOW);    
            digitalWrite(MOTOR_A_PIN2, LOW);    
            digitalWrite(MOTOR_B_PIN1, LOW);    
            digitalWrite(MOTOR_B_PIN2, LOW);   
            break;

    }
}

void testMotor()
{
    move(FORWARD);
    delayMicroseconds(2000);
    move(STOP_MOVING);
    delayMicroseconds(2000);

    move(BACKWARD);
    delayMicroseconds(2000);
    move(STOP_MOVING);
    delayMicroseconds(2000);

    move(TURN_LEFT);
    delayMicroseconds(2000);
    move(STOP_MOVING);
    delayMicroseconds(2000);

    move(TURN_RIGHT);
    delayMicroseconds(2000);
    move(STOP_MOVING);
    delayMicroseconds(2000);
}


