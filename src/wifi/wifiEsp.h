#pragma once
#ifndef _WIFIESP_H_
#define _WIFIESP_H_

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
class WifiEsp
{
private:
    const char *ssid = "bomba";
    const char *password = "bomba";

public:
    void wifi_Innit();
    bool loopWifi();
    bool loopWifi(int ultrasoonSensor, bool REED, int* irArray);

private:
    String printIR_Data(int* irArray);
};

#endif