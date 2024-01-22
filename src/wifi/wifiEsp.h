#pragma once
#ifndef _WIFIESP_H_
#define _WIFIESP_H_

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

#define IDLE    0
#define START   1
#define STOP    2 

class WifiEsp
{
private:
    const char *ssid = "bomba";
    const char *password = "bombaBomba";

public:
    //need to call serial.begin(buadrate); to make this methode work
    void wifi_Innit(); 

    int loopWifi();
    int loopWifi(int ultrasoonSensor, bool REED, int* irArray);

private:
    String printIR_Data(int* irArray);
    void printBaseHtml(WiFiClient &client);

};

#endif