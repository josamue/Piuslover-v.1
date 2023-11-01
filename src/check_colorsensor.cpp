
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include <SPI.h> 

#include "check_colorsensor.h"

bool blue = false;
bool black = false;

Adafruit_TCS34725 color_sensor = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void check_color()
{
    blue = false;
    black = false;
    delay(1);
    /*
    uint16_t r, g, b, c, colorTemp, lux;
    delay(60);
    color_sensor.getRawData(&r, &g, &b, &c);
    delay(60);
    colorTemp = color_sensor.calculateColorTemperature_dn40(r, g, b, c);
    lux = color_sensor.calculateLux(r, g, b);
    if(Farben_im_Bereich)
    {
        blue = true;
    }
    if (Farben_im_Bereich)
    {
        black = true;
    }*/
}