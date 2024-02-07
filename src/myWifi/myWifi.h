#ifndef __MYWIFI_H__
#define __MYWIFI_H__

#include <WiFi.h>
#include <SPIFFS.h>
#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>

enum WifiState
{
  idle = 0,
  start = 1,
  stop = 2
};

void startWifi();
bool getWifiState();
void setSensorData_In_Json(String carState, int ultrasoon, int* IRs, int REED);

#endif