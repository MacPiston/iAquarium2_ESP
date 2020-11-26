#include <Arduino.h>
#include <ArduinoOTA.h>
#include "config.h"
#include "setup.h"

void setup() {
    pinSetup();
    screenSetup();
    wifiSetup();
}

void loop() {
    ArduinoOTA.handle();
}