#define configUSE_PREEMPTION 0

#include <Arduino.h>
#include "car.h"
#include "websocket.h"
#include <WiFi.h>
#include <WiFiMulti.h>
#include "esp32ota.h"


WiFiMulti WiFiMulti;




#define USE_SERIAL Serial
extern unsigned long t=0;


TaskHandle_t WifiTask;
TaskHandle_t WebSocketTask;
TaskHandle_t ControlTask; 
TaskHandle_t OTATask;

void wifiInit(void){
	WiFi.disconnect();
    USE_SERIAL.print("Connecting Wifi");
	int num = 0;
	while(WiFiMulti.run() != WL_CONNECTED){
		delay(500);
    	USE_SERIAL.print(".");
		if (num++>50) ESP.restart();
		if (num%10==0) WiFiMulti.run();
	}

    USE_SERIAL.println("Connected");
}
void setup() {
	xTaskCreate(controlTask,"taskControl", 4096, NULL, 1, &ControlTask);
	// USE_SERIAL.begin(921600);
	USE_SERIAL.begin(115200);
	//Serial.setDebugOutput(true);
	USE_SERIAL.setDebugOutput(true);


	for(uint8_t t = 4; t > 0; t--) {
		USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
		USE_SERIAL.flush();
		delay(300);
	}
	
	xTaskCreate(wifiTask,"taskWifi", 4096, NULL, 1, &WifiTask);

}

void loop() {
	Serial.print("");
	//vTaskDelay(1);
}
void wifiTask(void *pvParameter){
	WiFiMulti.addAP("L2D", "l2dadambot");
    WiFiMulti.addAP("CRETA-KD","yoursolution");
	wifiInit();
	xTaskCreate(wsTask,"taskWebsocket", 4096, NULL, 1, &WebSocketTask);
	xTaskCreate(otaTask,"taskOTA", 4096, NULL, 1, &OTATask);
	for(;;){
		while (WiFi.status()!=WL_CONNECTED){
			wifiInit();
		}
		// if (WiFi.ping("google.com")!=WL_PING_SUCCESS){
		// 	wifiInit();
		// }
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
	vTaskDelete(ControlTask);
	for(;;){
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

void otaTask(void *pvParameter){
	while (!esp32otaInit("/ch")) vTaskDelay(1000/portTICK_PERIOD_MS);
	for(;;){
		esp32otaLoop();
		vTaskDelay(100/portTICK_PERIOD_MS);
	}
}