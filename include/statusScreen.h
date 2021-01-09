//
// Created by Maciej Zajecki on 26/11/2020.
//
#ifndef IAQUARIUM2_ESP_STATUSSCREEN_H
#define IAQUARIUM2_ESP_STATUSSCREEN_H

#include "wifiHelpers.h"
#include "config.h"
#include <ctime>

/**
 * Update status bar: time, WiFi signal strength,
 */
void updateStatusBar() {
    canvas->writeFillRect(0, 0, 128, 16, WHITE);
    canvas->setTextColor(BLACK);
    canvas->setCursor(2, 5);
    canvas->setTextSize(1);

    canvas->print(getWiFiStrengthPercentage());

    canvas->setCursor(32, 1);
    canvas->setTextSize(2);
    canvas->println(&currentTime, "%H:%M");
}

/**
 * Update main status screen: water params, next time-based action
 */
void updateStatusScreen(int id) {
    canvas->setTextColor(WHITE);
    switch (id) {
        case 0: // Main screen
            canvas->setTextSize(2);
            canvas->setCursor(0, 16);
            canvas->print("Tmp:");
            canvas->print(tempCread);
            canvas->setCursor(0, 32);
            canvas->print("TDS:");
            canvas->print(tdsRead);
            canvas->setCursor(0, 48);
            canvas->print("pH:");
            canvas->print(phRead);
            break;
        case 1:

            break;
        case 2:

            break;
        default: ;

    }
}

#endif //IAQUARIUM2_ESP_STATUSSCREEN_H
