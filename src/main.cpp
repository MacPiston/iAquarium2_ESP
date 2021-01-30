#include <Arduino.h>
#include <ArduinoOTA.h>
#include "config.h"
#include "setup.h"
#include "statusScreen.h"
#include "actions.h"

void setup() {
    pinSetup();
    sensorSetup();
    screenSetup();
    wifiSetup();
    setupTimers();
    setupInterrupts();
    setupUserActions();
    oled.clearDisplay();
}

void loop() {
#ifdef OTA_UPDATE
    ArduinoOTA.handle();
#endif
    // Check for refresh flag
    if (twoSecTriggered) {
        digitalWrite(STATUS_LED, HIGH);

        // Update sensor readings
        readWaterTemp();
        readWaterPh();
        readWaterTds();
        readWaterLeak();
        measurementCounter++;
        if (measurementCounter == 5) measurementCounter = 0;

        // Update status screen
        canvas->fillScreen(BLACK);
        updateStatusBar();
        updateStatusScreen(screenId);
        oled.drawBitmap(0, 0, canvas->getBuffer(), 128, 64, WHITE, BLACK);
        oled.display();

        digitalWrite(STATUS_LED, LOW);
        twoSecTriggered = false;
    }

    if (fifteenSecTriggered) {
        fetchCurrentTime();
        checkForActions();
        fifteenSecTriggered = false;
    }

    if (leakRead < 10) {
        digitalWrite(BUZZER, HIGH);
        screenId = 3;
    } else {
        digitalWrite(BUZZER, LOW);
    }

    // Update relays outputs
    digitalWrite(RELAY1, relays[0]);
    digitalWrite(RELAY2, relays[1]);
    digitalWrite(RELAY3, relays[2]);
}