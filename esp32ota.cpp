#include "esp32ota.h"
#include <AsyncElegantOTA.h>
AsyncWebServer OTAserver(80);
bool esp32otaInit(String path){
    if (WiFi.status() != WL_CONNECTED) return false;
    OTAserver.on(path.c_str(), HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", "Hi! I am ESP32.");
    });

    AsyncElegantOTA.begin(&OTAserver);    // Start ElegantOTA
    OTAserver.begin();
    return true;
}
void esp32otaLoop(void){
    AsyncElegantOTA.loop();
}