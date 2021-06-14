
#include <Arduino.h>
#include "car.h"
#include "websocket.h"
#include <WiFi.h>
#include <WiFiMulti.h>



WiFiMulti WiFiMulti;


#define USE_SERIAL Serial
extern unsigned long t=0;

void setup() {
	// USE_SERIAL.begin(921600);
	USE_SERIAL.begin(115200);
    motorInit();
	//Serial.setDebugOutput(true);
	USE_SERIAL.setDebugOutput(true);


	for(uint8_t t = 4; t > 0; t--) {
		USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
		USE_SERIAL.flush();
		delay(300);
	}

	WiFiMulti.addAP("L2D", "l2dadambot");
    WiFiMulti.addAP("CRETA-KD","yoursolution");

	WiFi.disconnect();
    USE_SERIAL.print("Connecting Wifi");
	while(WiFiMulti.run() != WL_CONNECTED) {
		delay(500);
    USE_SERIAL.print(".");
	}
    USE_SERIAL.println("Connected");
	webSocketInit();
    USE_SERIAL.println("Listening ...");
}

void loop() {
  webSocketLoop();
  if (millis()-t<10){
    stopAll();
    t=0;
    //stopAll();
  }
}
