//
// Created by Maciej Zajecki on 28/11/2020.
//

#ifndef IAQUARIUM2_ESP_SENSORREADERS_H
#define IAQUARIUM2_ESP_SENSORREADERS_H

void readWaterTemp() {
    waterTempSensor.requestTemperatures();
    tempsC[measurementCounter] = waterTempSensor.getTempCByIndex(0);
    tempCread = 0;
    for (float i : tempsC) {
        tempCread += i;
    }
    tempCread = tempCread / 5;
}

void readWaterPh() {
    float sensorVcc = 3.3;
    float averageVoltage = 0;
    float offset = 48.02740741;

    averageVoltage = analogRead(PH_ANALOG) * sensorVcc / (4095);
    ph[measurementCounter] = -19.18518519 * averageVoltage + offset;

    phRead = 0;
    for (float p : ph) {
        phRead += p;
    }
    phRead = phRead / 5;
}

void readWaterTds() {
    float sensorVcc = 3.3;
    float averageVoltage = 0;

    averageVoltage = analogRead(TDS_ANALOG) * sensorVcc / (4095);
    float compCoeff = 1.0 + 0.02 * (23 - 25);
    float compVolt = averageVoltage / compCoeff;
    tds[measurementCounter] = 0.5 * compVolt * (133.42 * compVolt * compVolt - 255.86 * compVolt + 857.39);

    tdsRead = 0;
    for (float td : tds) {
        tdsRead += td;
    }
    tdsRead = tdsRead / 5;
}

void readWaterLeak() {
    leak[measurementCounter] = touchRead(LEAK_CAPACITIVE);

    for (float l : leak) {
        leakRead += l;
    }
    leakRead = leakRead / 5;
}

#endif //IAQUARIUM2_ESP_SENSORREADERS_H
