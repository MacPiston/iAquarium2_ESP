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
    // Hardware buttons
    pinMode(BUTTON1, INPUT_PULLUP);
    pinMode(BUTTON2, INPUT_PULLUP);
    pinMode(BUTTON3, INPUT_PULLUP);
    pinMode(BUTTON4, INPUT_PULLUP);

    // Relays
    pinMode(RELAY1, OUTPUT);
    pinMode(RELAY2, OUTPUT);
    pinMode(RELAY3, OUTPUT);

    // Sensors
    adcAttachPin(PH_ANALOG);
    adcAttachPin(TDS_ANALOG);
    analogSetSamples(8);

    // Peripherals
    pinMode(STATUS_LED, OUTPUT);
}

void sensorSetup() {
    waterTempSensor.begin();
}

void screenSetup() {
#ifdef OLED_SPI
// TODO
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
    oled.print("iAquariumESP ");
    oled.print(VER);
    oled.display();
}

void serverSetup() {
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        if (leakRead < 10) {
            request->send(SPIFFS, "/leak.html", String(), false, statusPlaceholderProcessor);
        } else {
            request->send(SPIFFS, "/index.html", String(), false, statusPlaceholderProcessor);
        }
    });
    server.on("/index.html", HTTP_GET, [](AsyncWebServerRequest *request){
        if (leakRead < 10) {
            request->send(SPIFFS, "/leak.html", String(), false, statusPlaceholderProcessor);
        } else {
            request->send(SPIFFS, "/index.html", String(), false, statusPlaceholderProcessor);
        }
    });
    server.on("/index.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/index.css", "text/css");
    });
    server.on("/timeActions.html", HTTP_GET, [](AsyncWebServerRequest *request){
        if (leakRead < 10) {
            request->send(SPIFFS, "/leak.html", String(), false, statusPlaceholderProcessor);
        } else {
            request->send(SPIFFS, "/timeActions.html", String(), false, timePlaceholderProcessor);
        }
    });
    server.on("/temperatureActions.html", HTTP_GET, [](AsyncWebServerRequest *request){
        if (leakRead < 10) {
            request->send(SPIFFS, "/leak.html", String(), false, statusPlaceholderProcessor);
        } else {
            request->send(SPIFFS, "/temperatureActions.html", String(), false, temperaturePlaceholderProcessor);
        }
    });
    server.on("/phActions.html", HTTP_GET, [](AsyncWebServerRequest *request){
        if (leakRead < 10) {
            request->send(SPIFFS, "/leak.html", String(), false, statusPlaceholderProcessor);
        } else {
            request->send(SPIFFS, "/phActions.html", String(), false, phPlaceholderProcessor);
        }
    });
    server.on("/tdsActions.html", HTTP_GET, [](AsyncWebServerRequest *request){
        if (leakRead < 10) {
            request->send(SPIFFS, "/leak.html", String(), false, statusPlaceholderProcessor);
        } else {
            request->send(SPIFFS, "/tdsActions.html", String(), false, tdsPlaceholderProcessor);
        }
    });
    server.on("/actions.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/actions.css", "text/css");
    });
    server.begin();
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
            configTime(0, 3600, ntpServer);
            fetchCurrentTime();
            if (!SPIFFS.begin(true)) {
                oled.setCursor(0, 40);
                oled.print("SPIFFS error!");
                for (;;);
            }
            serverSetup();
#ifdef FIREBASE
            //Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
            //Firebase.reconnectWiFi(true);
#endif
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
            for (;;);
        }
        oled.display();
    } else {
        oled.setCursor(0, 24);
        oled.print("Network not found");
        oled.display();
        for (;;);
    }
}

void setupTimers() {
    twoSecTimer = timerBegin(0, 8000, true);
    fifteenSecTimer = timerBegin(1, 8000, true);
}

void setupInterrupts() {
    attachInterrupt(BUTTON1, &button1Handler, FALLING);
    attachInterrupt(BUTTON2, &button2Handler, FALLING);
    attachInterrupt(BUTTON3, &button3Handler, FALLING);
    attachInterrupt(BUTTON4, &button4Handler, FALLING);

    timerAttachInterrupt(twoSecTimer, &handle2SecTimerInterrupt , true);
    timerAlarmWrite(twoSecTimer, 20000, true);
    timerAlarmEnable(twoSecTimer);

    timerAttachInterrupt(fifteenSecTimer, &handle15SecTimerInterrupt, true);
    timerAlarmWrite(fifteenSecTimer, 150000, true);
    timerAlarmEnable(fifteenSecTimer);
}

#endif //IAQUARIUM2_ESP_SETUP_H
