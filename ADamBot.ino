/*
 * WebSocketClient.ino
 *
 *  Created on: 24.05.2015
 *
 */

#include <Arduino.h>
#include "car.h"
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClientSecure.h>

#include <WebSocketsClient.h>


WiFiMulti WiFiMulti;
WebSocketsClient webSocket;

#define USE_SERIAL Serial
unsigned long t=0;
void hexdump(const void *mem, uint32_t len, uint8_t cols = 16) {
	const uint8_t* src = (const uint8_t*) mem;
	USE_SERIAL.printf("\n[HEXDUMP] Address: 0x%08X len: 0x%X (%d)", (ptrdiff_t)src, len, len);
	
	for(uint32_t i = 0; i < len; i++) {
		if(i % cols == 0) {
			USE_SERIAL.printf("\n[0x%08X] 0x%08X: ", (ptrdiff_t)src, i);
		}
		USE_SERIAL.printf("%02X ", *src);
		src++;
	}
	USE_SERIAL.printf("\n");
  
  //Code here
}

void carControl(int cmnd){
  Serial.println(cmnd);
  t=millis()+1000;
  if (cmnd ==1){
    m1();
  }
  else if (cmnd==2){
    m2();
  }
  else if (cmnd==3){
    m3();
  }
  else if (cmnd==4){
    m4();
  }
  else if (cmnd==5){
    m5();
  }
  else if (cmnd==6){
    m6();
  }
  else if (cmnd==7){
    m7();
  }
  else if (cmnd==8){
    m8();
  }
  else if (cmnd==9){
    m9();
  }
  else stopAll();
}
void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {

	switch(type) {
		case WStype_DISCONNECTED:
			USE_SERIAL.printf("[WSc] Disconnected!\n");
			break;
		case WStype_CONNECTED:
			USE_SERIAL.printf("[WSc] Connected to url: %s\n", payload);

			// send message to server when Connected
			webSocket.sendTXT("Connected");
			break;
		case WStype_TEXT:
			//USE_SERIAL.printf("[WSc] get text: %s\n", payload);
      carControl(int(payload[0])-48);
			// send message to server
			// webSocket.sendTXT("message here");
			break;
		case WStype_BIN:
			USE_SERIAL.printf("[WSc] get binary length: %u\n", length);
			hexdump(payload, length);

			// send data to server
			// webSocket.sendBIN(payload, length);
			break;
		case WStype_ERROR:			
		case WStype_FRAGMENT_TEXT_START:
		case WStype_FRAGMENT_BIN_START:
		case WStype_FRAGMENT:
		case WStype_FRAGMENT_FIN:
			break;
	}

}

void setup() {
	// USE_SERIAL.begin(921600);
	USE_SERIAL.begin(115200);
  motorInit();
	//Serial.setDebugOutput(true);
	USE_SERIAL.setDebugOutput(true);

	USE_SERIAL.println();
	USE_SERIAL.println();
	USE_SERIAL.println();

	for(uint8_t t = 4; t > 0; t--) {
		USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
		USE_SERIAL.flush();
		delay(1000);
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
	// server address, port and URL
	webSocket.begin("ws.uudamstudio.com", 1880, "/command");

	// event handler
	webSocket.onEvent(webSocketEvent);

	// use HTTP Basic Authorization this is optional remove if not needed
	//webSocket.setAuthorization("user", "Password");

	// try ever 5000 again if connection has failed
	webSocket.setReconnectInterval(100);
  USE_SERIAL.println("Listening ...");
}

void loop() {
	webSocket.loop();
  if (millis()-t<5){
    stopAll();
    t=0;
    //stopAll();
  }
}
