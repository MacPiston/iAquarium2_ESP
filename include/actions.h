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
#define TIME_USED 0

    /// TEMPERATURE
#define TEMP_HIGHER_USED 1
    tempHigherThanActionArray[0].setup(29.0, 1, true);
#define TEMP_LOWER_USED 1
    tempLowerThanActionArray[0].setup(25.0, 1, false);

    /// PH
#define PH_HIGHER_USED 0
#define PH_LOWER_USED 0

    /// TDS
#define TDS_HIGHER_USED 0
#define TDS_LOWER_USED 0

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
    /// READ HIGHER THAN ACTION
    for (int i = 0; i < TEMP_HIGHER_USED; i++) {
        if (tempCread > tempHigherThanActionArray[i].triggerValue) tempHigherThanActionArray[i].setRelays();
    }
    /// READ LOWER THAN ACTION
    for (int i = 0; i < TEMP_LOWER_USED; ++i) {
        if (tempCread < tempLowerThanActionArray[i].triggerValue) tempLowerThanActionArray[i].setRelays();
    }

    // PH
    /// READ HIGHER THAN ACTION
    for (int i = 0; i < PH_HIGHER_USED; i++) {
        if (phRead > phHigherThanActionArray[i].triggerValue) phHigherThanActionArray[i].setRelays();
    }
    /// READ LOWER THAN ACTION
    for (int i = 0; i < PH_LOWER_USED; i++) {
        if (phRead < phLowerThanActionArray[i].triggerValue) phLowerThanActionArray[i].setRelays();
    }

    // TDS
    /// READ HIGHER THAN ACTION
    for (int i = 0; i < TDS_HIGHER_USED; i++) {
        if (tdsRead > tdsHigherThanActionArray[i].triggerValue) tdsHigherThanActionArray[i].setRelays();
    }
    /// READ LOWER THAN ACTION
    for (int i = 0; i < TDS_LOWER_USED; ++i) {
        if (tdsRead < tdsLowerThanActionArray[i].triggerValue) tdsLowerThanActionArray[i].setRelays();
    }

}

#endif //IAQUARIUM2_ESP_TIMEACTION_H
