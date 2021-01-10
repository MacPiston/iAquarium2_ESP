//
// Created by Maciej Zajecki on 10/01/2021.
//

#ifndef IAQUARIUM2_ESP_TIMEACTION_H
#define IAQUARIUM2_ESP_TIMEACTION_H
// Available actions DO NOT TOUCH
#define NACTIONS 10
struct action {
    bool relay0;
    bool relay1;
    bool relay2;
} pack;

struct timeAction {
    tm triggerTime;
    action state;
    void setup(int hour, int min, bool r0, bool r1, bool r2) {
        this->triggerTime.tm_hour = hour;
        this->triggerTime.tm_min = min;
        this->state.relay0 = r0;
        this->state.relay1 = r1;
        this->state.relay2 = r2;
    }
    bool compareTime(int hour, int min) {
        if (this->triggerTime.tm_hour == hour) {
            if (this->triggerTime.tm_min == min) return true;
        }
        return false;
    }
    void setRelays() {
        relays[0] = this->state.relay0;
        relays[1] = this->state.relay1;
        relays[2] = this->state.relay2;
    }
};

struct tempAction {
    float triggerValue;
    action state;
    void setup(float trigger, bool r0, bool r1, bool r2) {
        this->triggerValue = trigger;
        this->state.relay0 = r0;
        this->state.relay1 = r1;
        this->state.relay2 = r2;
    }
    void setRelays() {
        relays[0] = this->state.relay0;
        relays[1] = this->state.relay1;
        relays[2] = this->state.relay2;
    }
};

struct phAction {
    float triggerValue;
    action state;
    void setup(float trigger, bool r0, bool r1, bool r2) {
        this->triggerValue = trigger;
        this->state.relay0 = r0;
        this->state.relay1 = r1;
        this->state.relay2 = r2;
    }
    void setRelays() {
        relays[0] = this->state.relay0;
        relays[1] = this->state.relay1;
        relays[2] = this->state.relay2;
    }
};

struct tdsAction {
    float triggerValue;
    action state;
    void setup(float trigger, bool r0, bool r1, bool r2) {
        this->triggerValue = trigger;
        this->state.relay0 = r0;
        this->state.relay1 = r1;
        this->state.relay2 = r2;
    }
    void setRelays() {
        relays[0] = this->state.relay0;
        relays[1] = this->state.relay1;
        relays[2] = this->state.relay2;
    }
};

struct timeAction timeActionArray[NACTIONS];
struct tempAction tempActionArray[NACTIONS];
struct phAction phActionArray[NACTIONS];
struct tdsAction tdsActionArray[NACTIONS];

// user-defined actions - ADD NEW ACTIONS HERE
void setupUserActions() {
    // TIME
#define TIME_USED 2
    timeActionArray[0].setup(8, 0, true, false, false);
    timeActionArray[1].setup(21, 30, false, false, false);

    // TEMP
#define TEMP_USED 0

    // PH
#define PH_USED 0

    // TDS
#define TDS_USED 0

}

void checkForTimeActions() {
    int currentHour = currentTime.tm_hour;
    int currentMin = currentTime.tm_min;

    // TIME
    for (int i = 0; i < TIME_USED; i++) {
        if (timeActionArray[i].compareTime(currentHour, currentMin)) {
            timeActionArray[i].setRelays();
        }
    }

    // TEMP
    for (int i = 0; i < TEMP_USED; i++) {
        // HIGHER THAN READ
        if (tempActionArray[i].triggerValue > tempCread) {

        }
        // LOWER THAN READ
        else if (tempActionArray[i].triggerValue < tempCread) {

        }
    }

    // PH
    for (int i = 0; i < PH_USED; i++) {
        // HIGHER THAN READ
        if (phActionArray[i].triggerValue > phRead) {

        }
        // LOWER THAN READ
        else if (phActionArray[i].triggerValue < phRead) {

        }
    }

    // TDS
    for (int i = 0; i < TDS_USED; i++) {
        // HIGHER THEN READ
        if (tdsActionArray[i].triggerValue > tdsRead) {
            
        }
        // LOWER THAN READ
        else if (tdsActionArray[i].triggerValue < tdsRead) {

        }
    }

}

#endif //IAQUARIUM2_ESP_TIMEACTION_H
