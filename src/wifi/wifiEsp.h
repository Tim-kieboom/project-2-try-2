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
    bool loopWifi(uint8_t ir1, uint8_t ir2, int uds);
};

#endif