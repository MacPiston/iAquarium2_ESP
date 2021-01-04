//
// Created by Maciej Zajecki on 26/11/2020.
//
#ifndef IAQUARIUM2_ESP_STATUSSCREEN_H
#define IAQUARIUM2_ESP_STATUSSCREEN_H

#include "wifiHelpers.h"
#include <ctime>

/**
 * Update status bar: time, WiFi signal strength,
 */
void updateStatusBar() {
    oled.drawRect(0, 0, 128, 16, WHITE);
    oled.writeFillRect(0, 0, 128, 16, WHITE);
    oled.setTextColor(BLACK);

    oled.setCursor(2, 7);
    oled.setTextSize(1);
    char *temp = new char[3];
    sprintf(temp, "%d", getWiFiStrengthPercentage());
    oled.print(temp);
    delete[] temp;

    oled.setCursor(32, 1);
    oled.setTextSize(2);
    oled.println(&currentTime, "%H:%M");
}

/**
 * Update main status screen: water params, next time-based action
 */
void updateStatusScreen(int id) {
    GFXcanvas1 canvas(128, 48);

    switch (id) {
        case 1: // Main screen
            canvas.setTextSize(2);
            canvas.setCursor(0, 0);
            canvas.print("Temp.:");

            canvas.setCursor(0, 16);
            canvas.print("TDS:");

            break;
        case 2:

            break;
        case 3:

            break;
        default: ;

    }
    oled.drawBitmap(0, 16, canvas.getBuffer(), 128, 48, WHITE);
}

#endif //IAQUARIUM2_ESP_STATUSSCREEN_H
