//
// Created by Maciej Zajecki on 26/11/2020.
//

#ifndef IAQUARIUM2_ESP_WIFIHELPERS_H
#define IAQUARIUM2_ESP_WIFIHELPERS_H

#include "time.h"

/**
 * Tries connecting to provided WiFi network
 * @return Is WiFi connected
 */
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

/**
 * Fetches time from server and sets currentTime variable
 */
void IRAM_ATTR fetchCurrentTime() {
    if (WiFi.status() == WL_CONNECTED) {
        getLocalTime(&currentTime);
    }
}

int getWiFiStrengthPercentage() {
    return 2 * (100 + WiFi.RSSI());
}

String placeholderProcessor(const String& var) {
    return String();
}

#endif //IAQUARIUM2_ESP_WIFIHELPERS_H
