#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <utility/imumaths.h>
#include <VL53L0X.h>
#include <SPI.h> 

#include "one_tile.h"

#include "motors.h"
#include "check_ToF_sensors.h"
#include "check_colorsensor.h"
#include "balance_out.h"

int distance_front_start = 0;
int distance_back_start = 0;

bool back_in_black;

long Time_start;

void one_tile_forward(int speed_right, int speed_left)
{
    back_in_black = false;
    distance_front_start = distanceFrontRight();
    distance_back_start  = distanceBackRight();
    Forward(speed_right, speed_left);
    if(distance_front_start > 1000)
    {
        Time_start = millis();
        while(millis() - Time_start < 5000)
        {
            check_color();
            balancing(speed_right, speed_left);
            if(distanceFrontRight() - distance_back_start >= 280)
            {
                speed_left = speed_left / 4;
                speed_right = speed_right /4;
                Forward(speed_right, speed_left);
            }
            if(distanceBackRight() - distance_back_start >= 300)
            {
                break;
            }
            if(distanceFrontRight() < 30)
            {
                break;
            }
            else if(black)
            {
                Backwards(120, 120);
                while (distanceBackRight() > distance_back_start)
                {
                    delay(5);
                }
                back_in_black = true;
                break;
            }
            delay(1);
        }
    }

    else
    {
        Time_start = millis();
        while(millis() - Time_start < 5000)
        {
            balancing(speed_right, speed_left);
            check_color();
            Serial.println(distanceFrontRight() - distance_front_start);
            if(distanceFrontRight() - distance_front_start <= -200)
            {
                Forward(speed_right / 4, speed_left / 4);
            }
            if(distanceFrontRight() - distance_front_start <= -250)
            {
                break;
            }
            if(distanceFrontRight() < 150)
            {
                break;
            }
            else if(black)
            {
                Backwards(speed_right, speed_left);
                while (distanceFrontRight() < distance_front_start)
                {
                    delay(5);
                }
                back_in_black = true;
                break;
            }
            delay(1);
        }
    }
    Stop_Motors();
}


void black_tile()
{
    check_surroundings();
    if(left_clear)
    {
        turn_left(254);
        one_tile_forward(255,255);
    }
    else if(back_clear)
    {
        turn_around(254);
    }
    else
    {
        turn_right(254);
    }
}