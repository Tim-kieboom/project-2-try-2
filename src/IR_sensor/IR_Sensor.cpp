#include <Arduino.h>
#include "IR_Sensor.h"

#define RECIEVER_PIN_IR0            36  
#define RECIEVER_PIN_IR1            39   
#define RECIEVER_PIN_IR2            34 
#define RECIEVER_PIN_IR3            14

void IR_Innit()
{
    pinMode(RECIEVER_PIN_IR0, INPUT);
    pinMode(RECIEVER_PIN_IR1, INPUT);
    pinMode(RECIEVER_PIN_IR2, INPUT);
    pinMode(RECIEVER_PIN_IR3, INPUT);
}

int* checkIR()
{
    int* IRs = new int[5];

    IRs[0] = digitalRead(RECIEVER_PIN_IR0);
    IRs[1] = digitalRead(RECIEVER_PIN_IR1);
    IRs[2] = digitalRead(RECIEVER_PIN_IR2);
    IRs[3] = digitalRead(RECIEVER_PIN_IR3);

    //this is a sentinel value to mark the end of the array
    IRs[4] = SENTINEL_VALUE;

    return IRs;
}

void printIR_Data()
{
    int* IRs = checkIR();

    String message = "";
    String irString = "";
    uint8_t i =0;

    while(IRs[i] != SENTINEL_VALUE)
    {
        irString = (IRs[i] == 0) ? "not detect" : "detect";

        message += "[IR" + String(i) + "]: ";

        message +=  irString + ", ";     

        i++;  
    }

    Serial.println(message);

    delete[] IRs;
}
 