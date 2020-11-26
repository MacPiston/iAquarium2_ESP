//
// Created by Maciej Zajecki on 19/11/2020.
//
#include "Arduino.h"
#include "WiFi.h"

#ifndef IAQUARIUM2_ESP_SETUP_H
#define IAQUARIUM2_ESP_SETUP_H

void pinSetup() {
    // Touch buttons
    //touchAttachInterrupt(TOUCH1, {}, THRESHOLD);
    //touchAttachInterrupt(TOUCH2, {}, THRESHOLD);
    //touchAttachInterrupt(TOUCH3, {}, THRESHOLD);
    //touchAttachInterrupt(TOUCH4, {}, THRESHOLD);

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

bool connectToWiFi() {
    WiFi.begin(ssid, password);
    int counter = 0;
    while (WiFi.status() != WL_CONNECTED && counter < 10) {
        delay(1000);
        counter++;
    }
    if (WiFi.status() == WL_CONNECTED) {
        return true;
    } else {
        return false;
    }
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

#endif //IAQUARIUM2_ESP_SETUP_H
