#define configUSE_PREEMPTION 0

#include <Arduino.h>
#include "car.h"
#include "websocket.h"
#include <WiFi.h>
#include <WiFiMulti.h>



WiFiMulti WiFiMulti;




#define USE_SERIAL Serial
extern unsigned long t=0;


TaskHandle_t WifiTask;
TaskHandle_t WebSocketTask;
TaskHandle_t ControlTask; 

void wifiInit(void){
	WiFi.disconnect();
    USE_SERIAL.print("Connecting Wifi");
	while(WiFiMulti.run() != WL_CONNECTED) {
		delay(500);
    USE_SERIAL.print(".");
	}
    USE_SERIAL.println("Connected");
}
void setup() {
	// USE_SERIAL.begin(921600);
	USE_SERIAL.begin(115200);
	//Serial.setDebugOutput(true);
	USE_SERIAL.setDebugOutput(true);


	for(uint8_t t = 4; t > 0; t--) {
		USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
		USE_SERIAL.flush();
		delay(300);
	}
	xTaskCreate(controlTask,"taskControl", 4096, NULL, 1, NULL);
	xTaskCreate(wifiTask,"taskWifi", 4096, NULL, 1, NULL);

}

void loop() {
	Serial.print("");
	//vTaskDelay(1);
}
void wifiTask(void *pvParameter){
	WiFiMulti.addAP("L2D", "l2dadambot");
    WiFiMulti.addAP("CRETA-KD","yoursolution");
	wifiInit();
	xTaskCreate(wsTask,"taskWebsocket", 4096, NULL, 1, NULL);
	for(;;){
		while (WiFi.status()!=WL_CONNECTED){
			wifiInit();
		}
		vTaskDelay(60000/portTICK_PERIOD_MS);
	}
}
void wsTask(void *pvParameter){
	webSocketInit();
	USE_SERIAL.println("Listening ...");
	for(;;){
		webSocketLoop();
		vTaskDelay(1/portTICK_PERIOD_MS);
	}
}
void controlTask(void *pvParameter){
	motorInit();
	for(;;){
		if (millis()-t<10){
    	stopAll();
    	t=0;
    	//stopAll();
		vTaskDelay(8/portTICK_PERIOD_MS);
 		}
	}
}