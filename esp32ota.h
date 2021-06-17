#ifndef _ESP32OTA__H_
#define _ESP32OTA__H_

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>



bool esp32otaInit(String path);
void esp32otaLoop(void);
#endif