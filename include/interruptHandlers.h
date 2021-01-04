//
// Created by Maciej Zajecki on 28/11/2020.
//

#ifndef IAQUARIUM2_ESP_INTERRUPTHANDLERS_H
#define IAQUARIUM2_ESP_INTERRUPTHANDLERS_H
#include "sensorReaders.h"
#include "esp_log.h"

/**
 * Handler called every 5s
 */
void IRAM_ATTR handle2SecTimerInterrupt() {
    //portENTER_CRITICAL_ISR(&mux);
    twoSecTriggered = true;
    //portEXIT_CRITICAL_ISR(&mux);
}

void IRAM_ATTR handle15SecTimerInterrupt() {
    //portENTER_CRITICAL_ISR(&mux);
    fifteenSecTriggered = true;
    //portEXIT_CRITICAL_ISR(&mux);
}

bool IRAM_ATTR checkButtonDebounce() {
    if ((esp_log_timestamp() - debounceTimer) > 150) {
        debounceTimer = esp_log_timestamp();
        return true;
    }
    return false;
}

void IRAM_ATTR button1Handler() {
    portENTER_CRITICAL_ISR(&mux);
    if (checkButtonDebounce()) {
        screenId++;
        if (screenId == 4) screenId = 0;
        twoSecTriggered = true;
    }
    portEXIT_CRITICAL_ISR(&mux);
}

void IRAM_ATTR button2Handler() {
    portENTER_CRITICAL_ISR(&mux);
    if (checkButtonDebounce()) {
        if (relays[0]) {
            relays[0] = false;
        } else {
            relays[0] = true;
        }
    }
    portEXIT_CRITICAL_ISR(&mux);
}

void IRAM_ATTR button3Handler() {
    portENTER_CRITICAL_ISR(&mux);
    if (checkButtonDebounce()) {
        if (relays[1]) {
            relays[1] = false;
        } else {
            relays[1] = true;
        }
    }
    portEXIT_CRITICAL_ISR(&mux);
}

void IRAM_ATTR button4Handler() {
    portENTER_CRITICAL_ISR(&mux);
    if (checkButtonDebounce()) {
        if (relays[2]) {
            relays[2] = false;
        } else {
            relays[2] = true;
        }
    }
    portEXIT_CRITICAL_ISR(&mux);
}

#endif //IAQUARIUM2_ESP_INTERRUPTHANDLERS_H
