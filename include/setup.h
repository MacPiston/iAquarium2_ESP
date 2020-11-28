//
// Created by Maciej Zajecki on 19/11/2020.
//
#include "Arduino.h"
#include "WiFi.h"
#include "wifiHelpers.h"
#include "statusScreen.h"
#include "interruptHandlers.h"

#ifndef IAQUARIUM2_ESP_SETUP_H
#define IAQUARIUM2_ESP_SETUP_H

void pinSetup() {
    // Touch buttons

    // Relays
    pinMode(RELAY1, OUTPUT);
    pinMode(RELAY2, OUTPUT);
    pinMode(RELAY3, OUTPUT);

    // Sensors
    adcAttachPin(PH_ANALOG);
    adcAttachPin(TDS_ANALOG);

    // Peripherals
//    pinMode(STATUS_LED, OUTPUT);
}

void sensorSetup() {
    waterTempSensor.begin();
}

void screenSetup() {
#ifdef OLED_SPI

#endif

#ifdef OLED_I2C
    oledI2C.begin(OLED_SDA, OLED_SCL, 100000);
    oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
#endif

    // OLED Welcome screen
    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.setTextSize(1);
    oled.setCursor(0, 0);
    oled.print("iAquariumESP v1.0");
    oled.display();
}

void wifiSetup() {
    oled.setCursor(0, 8);
    oled.print("Connecting WiFi...");
    oled.display();

    int networks = WiFi.scanNetworks();
    bool networkFound = false;

    for (int i = 0; i < networks; i++) {
        if (WiFi.SSID(i) == ssid) {
            oled.setCursor(0, 16);
            oled.print("Found " + WiFi.SSID(i) + "!");
            oled.display();
            networkFound = true;
        }
    }

    if (networkFound) {
        oled.setCursor(0, 24);
        if (connectToWiFi()) {
            oled.print("Connected!");
            oled.setCursor(0, 32);
            oled.print(WiFi.localIP());
#ifdef OTA_UPDATE
            ArduinoOTA
                    .onStart([]() {
                        String type;
                        if (ArduinoOTA.getCommand() == U_FLASH)
                            type = "sketch";
                        else // U_SPIFFS
                            type = "filesystem";

                        // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
                        Serial.println("Start updating " + type);
                    })
                    .onEnd([]() {
                        Serial.println("\nEnd");
                    })
                    .onProgress([](unsigned int progress, unsigned int total) {
                        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
                    })
                    .onError([](ota_error_t error) {
                        Serial.printf("Error[%u]: ", error);
                        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
                        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
                        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
                        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
                        else if (error == OTA_END_ERROR) Serial.println("End Failed");
                    });

            ArduinoOTA.begin();
#endif
        } else {
            oled.print("WiFi unav. (ATM)");
        }
        oled.display();
    } else {
        oled.setCursor(0, 24);
        oled.print("Network not found");
        oled.display();
    }
}

void setupTimers() {
    fiveSecTimer = timerBegin(0, 80, true);
}

void setupInterrupts() {
    //touchAttachInterrupt(TOUCH1, &button1Handler, THRESHOLD);
    //touchAttachInterrupt(TOUCH2, &button2Handler, THRESHOLD);
    //touchAttachInterrupt(TOUCH3, &button3Handler, THRESHOLD);
    //touchAttachInterrupt(TOUCH4, &button4Handler, THRESHOLD);

    timerAttachInterrupt(fiveSecTimer, &handle5SecTimerHandler , true);
    timerAlarmWrite(fiveSecTimer, 5000000, true);
    timerAlarmEnable(fiveSecTimer);
}

#endif //IAQUARIUM2_ESP_SETUP_H
