//
// Created by Maciej Zajecki on 19/11/2020.
//

#ifndef IAQUARIUM2_ESP_CONFIG_H
#define IAQUARIUM2_ESP_CONFIG_H
#include "Adafruit_SSD1306.h"

//----- WiFi -----
const char* ssid = "niewiem";
const char* password = "maciek2505";

//----- Touch buttons -----
#define THRESHOLD 40
#define TOUCH1 GPIO_NUM_4
#define TOUCH2 GPIO_NUM_0
#define TOUCH3 GPIO_NUM_2
#define TOUCH4 GPIO_NUM_15

//----- Relays -----
#define RELAY1 GPIO_NUM_25
#define RELAY2 GPIO_NUM_26
#define RELAY3 GPIO_NUM_27

//----- OLED Screen -----
#define OLED_I2C
//#define OLED_SPI

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#ifdef OLED_I2C
#define OLED_SDA GPIO_NUM_21
#define OLED_SCL GPIO_NUM_22
#define OLED_RST GPIO_NUM_23
    TwoWire oledI2C = TwoWire(0);
    Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &oledI2C, OLED_RST);
#endif

#ifdef OLED_SPI
#define OLED_MOSI GPIO_NUM_23
#define OLED_CLK GPIO_NUM_18
#define OLED_DC GPIO_NUM_16
#define OLED_CS GPIO_NUM_5
#define OLED_RST GPIO_NUM_17
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RST, OLED_CS);
#endif

//----- Sensors -----
#define PH_ANALOG GPIO_NUM_34
#define TDS_ANALOG GPIO_NUM_35
#define TEMP_1WIRE GPIO_NUM_32

//----- Peripherals -----
#define STATUS_LED GPIO_NUM_22

//----- Data -----
int phRead = 0;
int tdsRead = 0;


#endif //IAQUARIUM2_ESP_CONFIG_H
