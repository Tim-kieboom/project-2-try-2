#pragma once
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

//saves the sensor data in a json format so that when the webpage asks for it it sends this json.
void setSensorData_In_Json(String carState, int ultrasoon, int* IRs, int REED);
void setSensorData_toEmpty();

#endif