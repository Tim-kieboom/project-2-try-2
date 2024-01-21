#include <Arduino.h>

#define RECIEVER_PIN_IR1            36  
#define RECIEVER_PIN_IR2            39   
#define RECIEVER_PIN_IR3            40 
#define RECIEVER_PIN_IR4            41

void IR_Innit()
{
    pinMode(RECIEVER_PIN_IR1, INPUT);
    pinMode(RECIEVER_PIN_IR2, INPUT);
}

int* checkIR()
{
    int* IRs = new int[5];

    IRs[0] = digitalRead(RECIEVER_PIN_IR1);
    IRs[1] = digitalRead(RECIEVER_PIN_IR2);
    IRs[2] = digitalRead(RECIEVER_PIN_IR3);
    IRs[3] = digitalRead(RECIEVER_PIN_IR4);

    //this is a sentinel value to mark the end of the array
    IRs[4] = SENTINEL_VALUE;

    return IRs;
}

void printIR_Data()
{
    int* IRs = checkIR();

    String message = "";

    for(int i = 0; i < sizeof(IRs); i++)
    {
        message += "[IR" + String(i) + "]: ";

        message +=  String(IRs[i]), ", ";       
    }

    Serial.println(message);

    delete[] IRs;
}
 