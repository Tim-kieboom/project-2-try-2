#include <Arduino.h>
#include "mainHeader.h"

#define RECIEVER_PIN_IR1            36  
#define RECIEVER_PIN_IR2            39   

void IR_Innit()
{
    pinMode(RECIEVER_PIN_IR1, INPUT);
    pinMode(RECIEVER_PIN_IR2, INPUT);
}

int checkIR()
{
    if(digitalRead(RECIEVER_PIN_IR1) == LOW && digitalRead(RECIEVER_PIN_IR2) == LOW)
    {
        return FORWARD;
    }   
    else if(digitalRead(RECIEVER_PIN_IR1) == LOW)
    {
        return TURN_RIGHT;
    }
    else if(digitalRead(RECIEVER_PIN_IR2) == LOW)
    {
        return TURN_LEFT;
    }

    return WALL_DETECTED;
}