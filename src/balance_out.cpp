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

int difference_left()
{
    return(distanceLeftFront() - distanceLeftBack());
}

int difference_right()
{
    return(distanceRightFront() - distanceRightBack());
}

int difference_front()
{
    return(distanceFrontRight() - distanceFrontLeft());
}

int difference_back()
{
    return(distanceBackRight() - distanceBackLeft());
}

void balancing(int speed_right, int speed_left)
{
    check_surroundings();
    if(!right_clear)
    {
        if(difference_right() > 9)
        {
            Forward(speed_right / 1.5, speed_left);
        }
        else if(difference_right() < -9)
        {
            Forward(speed_right, speed_left / 1.5);
        }
        else
        {
            Forward(speed_right, speed_left);
        }
    }
    else if(!left_clear)
    {
        if(difference_left() > 9)
        {
            Forward(speed_right, speed_left / 1.5);
        }
        else if(difference_left() < -9)
        {
            Forward(speed_right / 1.5, speed_left);
        }
        else
        {
            Forward(speed_right, speed_left);
        }
    }
    else if(distanceFrontRight() < 1000 && distanceFrontLeft() < 1000)
    {
        if(difference_front() > 9)
        {
            Forward(speed_right, speed_left / 1.5);
        }
        else if(difference_front() < -9)
        {
            Forward(speed_right / 1.5, speed_left);
        }
        else
        {
            Forward(speed_right, speed_left);
        }
    }
    else if(distanceBackLeft() < 1000 && distanceBackRight() <1000)
    {
        if(difference_back() > 9)
        {
            Forward(speed_right / 1.5, speed_left);
        }
        else if(difference_back() < -9)
        {
            Forward(speed_right, speed_left / 1.5);
        }
        else
        {
            Forward(speed_right, speed_left);
        }
    }
    else
    {
        Forward(speed_right, speed_left);
    }
}