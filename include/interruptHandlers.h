//
// Created by Maciej Zajecki on 28/11/2020.
//

#ifndef IAQUARIUM2_ESP_INTERRUPTHANDLERS_H
#define IAQUARIUM2_ESP_INTERRUPTHANDLERS_H
#include "sensorReaders.h"

/**
 * Handler called every 5s
 */
void IRAM_ATTR handle5SecTimerHandler() {
    fiveSecTriggered = true;
}

void button1Handler() {

}

void button2Handler() {

}

void button3Handler() {

}

void button4Handler() {

}

#endif //IAQUARIUM2_ESP_INTERRUPTHANDLERS_H
