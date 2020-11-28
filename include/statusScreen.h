//
// Created by Maciej Zajecki on 26/11/2020.
//
#ifndef IAQUARIUM2_ESP_STATUSSCREEN_H
#define IAQUARIUM2_ESP_STATUSSCREEN_H

#include "wifiHelpers.h"
#include "time.h"

/**
 * Update status bar: time, WiFi signal strenght,
 */
void updateStatusBar() {
    oled.clearDisplay();
    oled.drawRect(0, 0, 128, 16, WHITE);
    oled.writeFillRect(0, 0, 128, 16, WHITE);
    oled.setCursor(0, 2);
    oled.setTextColor(BLACK);
    oled.println(&currentTime, "%H:%M");
    oled.display();
}

/**
 * Update main status screen: water params, next time-based action
 */
void updateStatusScreen() {

}

#endif //IAQUARIUM2_ESP_STATUSSCREEN_H
