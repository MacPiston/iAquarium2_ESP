//
// Created by Maciej Zajecki on 28/11/2020.
//

#ifndef IAQUARIUM2_ESP_SENSORREADERS_H
#define IAQUARIUM2_ESP_SENSORREADERS_H

void readWaterTemp() {
    tempsC[measurementCounter] = waterTempSensor.getTempCByIndex(0);
    tempCread = 0;
    for (int i = 0; i < 5; ++i) {
        tempCread += tempsC[i];
    }
    tempCread = tempCread / 5;
}

int getMedianNum(int bArray[], int iFilterLen)
{
    int bTab[iFilterLen];
    for (byte i = 0; i<iFilterLen; i++)
        bTab[i] = bArray[i];
    int i, j, bTemp;
    for (j = 0; j < iFilterLen - 1; j++)
    {
        for (i = 0; i < iFilterLen - j - 1; i++)
        {
            if (bTab[i] > bTab[i + 1])
            {
                bTemp = bTab[i];
                bTab[i] = bTab[i + 1];
                bTab[i + 1] = bTemp;
            }
        }
    }
    if ((iFilterLen & 1) > 0)
        bTemp = bTab[(iFilterLen - 1) / 2];
    else
        bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
    return bTemp;
}

void readWaterPh() {

}

void readWaterTds() {
    int samples = 30;
    float sensorVcc = 3.3;
    int analogReadBuffer[samples];
    float averageVoltage = 0;

    for (int i = 0; i < samples; ++i) {
        analogReadBuffer[i] = analogRead(TDS_ANALOG);
    }

    averageVoltage = getMedianNum(analogReadBuffer, samples) * sensorVcc / 4095;
    float compCoeff = 1.0 + 0.02 * (tempCread - 25);
    float compVolt = averageVoltage / compCoeff;
    tds[measurementCounter] = 0.5 * compVolt * (133.42 * compVolt * compVolt - 255.86 * compVolt + 857.39);

    tdsRead = 0;
    for (int i = 0; i < 5; ++i) {
        tdsRead += tds[i];
    }
    tdsRead = tdsRead / 5;
}

#endif //IAQUARIUM2_ESP_SENSORREADERS_H
