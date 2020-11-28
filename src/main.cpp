#include <Arduino.h>
#include <ArduinoOTA.h>
#include "config.h"
#include "setup.h"
#include "statusScreen.h"

void setup() {
    pinSetup();
    sensorSetup();
    screenSetup();
    wifiSetup();
    setupTimers();
    setupInterrupts();
}

void loop() {
#ifdef OTA_UPDATE
    ArduinoOTA.handle();
#endif
    // Check for refresh flag
    if (fiveSecTriggered) {
        // Update current time
        fetchCurrentTime();

        // Update sensor readings
        readWaterTemp();
        readWaterPh();
        readWaterTds();
        measurementCounter++;
        if (measurementCounter == 5) measurementCounter = 0;

        // Update status screen
        updateStatusBar();
        updateStatusScreen();

        fiveSecTriggered = false;
    }

    // Check for time-based actions

    // Check for sensor-based actions

}