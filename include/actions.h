//
// Created by Maciej Zajecki on 10/01/2021.
//

#ifndef IAQUARIUM2_ESP_TIMEACTION_H
#define IAQUARIUM2_ESP_TIMEACTION_H
// Available actions DO NOT TOUCH
#define NACTIONS 10
struct action {
    int relayId;
    bool relayState;
};

struct timeAction {
    tm triggerTime{};
    action state{};
    void setup(int hour, int min, int relay, bool r) {
        this->triggerTime.tm_hour = hour;
        this->triggerTime.tm_min = min;
        this->state.relayId = relay;
        this->state.relayState = r;
    }
    bool compareTime(int hour, int min) {
        if (this->triggerTime.tm_hour == hour) {
            if (this->triggerTime.tm_min == min) return true;
        }
        return false;
    }
    void setRelays() {
        relays[this->state.relayId] = this->state.relayState;
    }
};

struct tempAction {
    float triggerValue;
    action state;
    void setup(float trigger, int relay, bool r) {
        this->triggerValue = trigger;
        this->state.relayId = relay;
        this->state.relayState = r;
    }
    void setRelays() {
        relays[this->state.relayId] = this->state.relayState;
    }
};

struct phAction {
    float triggerValue;
    action state;
    void setup(float trigger, int relay, bool r) {
        this->triggerValue = trigger;
        this->state.relayId = relay;
        this->state.relayState = r;
    }
    void setRelays() {
        relays[this->state.relayId] = this->state.relayState;
    }
};

struct tdsAction {
    float triggerValue;
    action state;
    void setup(float trigger, int relay, bool r) {
        this->triggerValue = trigger;
        this->state.relayId = relay;
        this->state.relayState = r;
    }
    void setRelays() {
        relays[this->state.relayId] = this->state.relayState;
    }
};

struct timeAction timeActionArray[NACTIONS];
struct tempAction tempHigherThanActionArray[NACTIONS];
struct tempAction tempLowerThanActionArray[NACTIONS];
struct phAction phHigherThanActionArray[NACTIONS];
struct phAction phLowerThanActionArray[NACTIONS];
struct tdsAction tdsHigherThanActionArray[NACTIONS];
struct tdsAction tdsLowerThanActionArray[NACTIONS];

/////////////////////////////////////////////////////////////////
// user-defined actions - ADD NEW ACTIONS HERE
void setupUserActions() {
    /// TIME
#define TIME_USED 2
    timeActionArray[0].setup(8, 0, 0, true);
    timeActionArray[1].setup(21, 30, 0, false);

    /// TEMPERATURE
#define TEMP_HIGHER_USED 1
    tempHigherThanActionArray[0].setup(24.4, 1, false);
#define TEMP_LOWER_USED 1
    tempLowerThanActionArray[0].setup(23.4, 1, true);

    /// PH
#define PH_HIGHER_USED 0
#define PH_LOWER_USED 1
    phLowerThanActionArray[0].setup(7.54, 3, true);

    /// TDS
#define TDS_HIGHER_USED 4
#define TDS_LOWER_USED 0
    tdsHigherThanActionArray[0].setup(543.0, 2, false);
    tdsHigherThanActionArray[1].setup(350.1, 2, true);
    tdsHigherThanActionArray[2].setup(444, 1, true);
    tdsHigherThanActionArray[3].setup(101, 3, false);

}
/////////////////////////////////////////////////////////////////

void checkForActions() {
    int currentHour = currentTime.tm_hour;
    int currentMin = currentTime.tm_min;

    // TIME
    for (int i = 0; i < TIME_USED; i++) {
        if (timeActionArray[i].compareTime(currentHour, currentMin)) timeActionArray[i].setRelays();
    }

    // TEMPERATURE
    /// HIGHER THAN READ
    for (int i = 0; i < TEMP_HIGHER_USED; i++) {
        if (tempHigherThanActionArray[i].triggerValue > tempCread) tempHigherThanActionArray[i].setRelays();
    }
    /// LOWER THAN READ
    for (int i = 0; i < TEMP_LOWER_USED; ++i) {
        if (tempLowerThanActionArray[i].triggerValue < tempCread) tempLowerThanActionArray[i].setRelays();
    }

    // PH
    /// HIGHER THAN READ
    for (int i = 0; i < PH_HIGHER_USED; i++) {
        if (phHigherThanActionArray[i].triggerValue > phRead) phHigherThanActionArray[i].setRelays();
    }
    /// LOWER THAN READ
    for (int i = 0; i < PH_LOWER_USED; i++) {
        if (phLowerThanActionArray[i].triggerValue < phRead) phLowerThanActionArray[i].setRelays();
    }

    // TDS
    /// HIGHER THEN READ
    for (int i = 0; i < TDS_HIGHER_USED; i++) {
        if (tdsHigherThanActionArray[i].triggerValue > tdsRead) tdsHigherThanActionArray[i].setRelays();
    }
    /// LOWER THAN READ
    for (int i = 0; i < TDS_LOWER_USED; ++i) {
        if (tdsLowerThanActionArray[i].triggerValue < tdsRead) tdsLowerThanActionArray[i].setRelays();
    }

}

#endif //IAQUARIUM2_ESP_TIMEACTION_H
