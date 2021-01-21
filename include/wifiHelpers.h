//
// Created by Maciej Zajecki on 26/11/2020.
//

#ifndef IAQUARIUM2_ESP_WIFIHELPERS_H
#define IAQUARIUM2_ESP_WIFIHELPERS_H

#include "time.h"
#include "actions.h"

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

String statusPlaceholderProcessor(const String &var) {
    char buffer[15];
    if (var == "TIMExx") {

    } else if (var == "TEMPxx") {
        sprintf(buffer, "%0.2f", tempCread);
        return buffer;
    } else if (var == "PHxxxx") {
        sprintf(buffer, "%0.1f", phRead);
        return buffer;
    } else if (var == "TDSxxx") {
        sprintf(buffer, "%0.0f", tdsRead);
        return buffer;
    }
    return "unknown";
}

String timePlaceholderProcessor(const String &var) {
    short value = var.toInt();

    if (value < 10) {
        // Hour row
        if (value < TIME_USED) {
            tm time = timeActionArray[value].triggerTime;
            return String(time.tm_hour) + ":" + String(time.tm_min);
        }
    } else if (value < 20) {
        // Action row
        value -= 10;
        if (value < TIME_USED) return timeActionArray[value].state.relayState ? "On" : "Off";
    } else if (value < 30) {
        // Relay row
        value -= 20;
        if (value < TIME_USED) return String(timeActionArray[value].state.relayId);
    }
    return "";
}

String temperaturePlaceholderProcessor(const String &var) {
    short value = var.toInt();

    if (value < 30) { // Greater than measurement
        if (value < 10) {
            // Value row
            if (value < TEMP_HIGHER_USED) return String(tempHigherThanActionArray[value].triggerValue);
        } else if (value < 20) {
            // Action row
            value -= 10;
            if (value < TEMP_HIGHER_USED) return tempHigherThanActionArray[value].state.relayState ? "On" : "Off";
        } else if (value < 30) {
            // Relay row
            value -= 20;
            if (value < TEMP_HIGHER_USED) return String(tempHigherThanActionArray[value].state.relayId);
        }
    } else if (value < 60) { // Lower than measurement
        if (value < 40) {
            // Value row
            value -= 30;
            if (value < TEMP_LOWER_USED) return String(tempLowerThanActionArray[value].triggerValue);
        } else if (value < 50) {
            // Action row
            value -= 40;
            if (value < TEMP_LOWER_USED) return tempLowerThanActionArray[value].state.relayState ? "On" : "Off";
        } else if (value < 60) {
            // Relay row
            value -= 50;
            if (value < TEMP_LOWER_USED) return String(tempLowerThanActionArray[value].state.relayId);
        }
    }

    return "";
}

String phPlaceholderProcessor(const String &var) {
    short value = var.toInt();

    if (value < 30) { // Greater than measurement
        if (value < 10) {
            // Value row
            if (value < PH_HIGHER_USED) return String(phHigherThanActionArray[value].triggerValue);
        } else if (value < 20) {
            // Action row
            value -= 10;
            if (value < PH_HIGHER_USED) return phHigherThanActionArray[value].state.relayState ? "On" : "Off";
        } else if (value < 30) {
            // Relay row
            value -= 20;
            if (value < PH_HIGHER_USED) return String(phHigherThanActionArray[value].state.relayId);
        }
    } else if (value < 60) { // Lower than measurement
        if (value < 40) {
            // Value row
            value -= 30;
            if (value < PH_LOWER_USED) return String(phLowerThanActionArray[value].triggerValue);
        } else if (value < 50) {
            // Action row
            value -= 40;
            if (value < PH_LOWER_USED) return phLowerThanActionArray[value].state.relayState ? "On" : "Off";
        } else if (value < 60) {
            // Relay row
            value -= 50;
            if (value < PH_LOWER_USED) return String(phLowerThanActionArray[value].state.relayId);
        }
    }

    return "";
}

String tdsPlaceholderProcessor(const String &var) {
    short value = var.toInt();

    if (value < 30) { // Greater than measurement
        if (value < 10) {
            // Value row
            if (value < TDS_HIGHER_USED) return String(tdsHigherThanActionArray[value].triggerValue);
        } else if (value < 20) {
            // Action row
            value -= 10;
            if (value < TDS_HIGHER_USED) return tdsHigherThanActionArray[value].state.relayState ? "On" : "Off";
        } else if (value < 30) {
            // Relay row
            value -= 20;
            if (value < TDS_HIGHER_USED) return String(tdsHigherThanActionArray[value].state.relayId);
        }
    } else if (value < 60) { // Lower than measurement
        if (value < 40) {
            // Value row
            value -= 30;
            if (value < TDS_LOWER_USED) return String(tdsLowerThanActionArray[value].triggerValue);
        } else if (value < 50) {
            // Action row
            value -= 40;
            if (value < TDS_LOWER_USED) return tdsLowerThanActionArray[value].state.relayState ? "On" : "Off";
        } else if (value < 60) {
            // Relay row
            value -= 50;
            if (value < TDS_LOWER_USED) return String(tdsLowerThanActionArray[value].state.relayId);
        }
    }

    return "";
}

#endif //IAQUARIUM2_ESP_WIFIHELPERS_H
