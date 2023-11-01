#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <utility/imumaths.h>
#include <SPI.h>

#include "motors.h"

Adafruit_BNO055 Gyro = Adafruit_BNO055(55);

int Motor_right_front_direction = 4;
int Motor_right_front_speed = 3;
int Motor_right_back_direction = 7;
int Motor_right_back_speed = 6;

int Motor_left_front_direction = 12;
int Motor_left_front_speed = 11;
int Motor_left_back_direction = 8;
int Motor_left_back_speed = 5;

int orientation_start = 0;
int orientation_value = 0;

int east = 90;
int south = 180;
int west = 270;
int north = 360;

int start_east = 45;
int start_south = 135;
int start_west = 225;
int start_north = 315;

int estimated_angle = 0;
int estimated_direction = 0;

int Gyro_reset_pin = 62;

unsigned long Time_start_motors;

void Forward(int speed_right, int speed_left)
{
  digitalWrite(Motor_right_front_direction, HIGH);
  analogWrite(Motor_right_front_speed, speed_right);

  digitalWrite(Motor_right_back_direction, LOW);
  analogWrite(Motor_right_back_speed, speed_right);

  digitalWrite(Motor_left_front_direction, HIGH);
  analogWrite(Motor_left_front_speed, speed_left);

  digitalWrite(Motor_left_back_direction, LOW);
  analogWrite(Motor_left_back_speed, speed_left);
}

void Start_left(int speed)
{
  digitalWrite(Motor_right_front_direction, HIGH);
  analogWrite(Motor_right_front_speed, speed);

  digitalWrite(Motor_right_back_direction, LOW);
  analogWrite(Motor_right_back_speed, speed);

  digitalWrite(Motor_left_front_direction, LOW);
  analogWrite(Motor_left_front_speed, speed);

  digitalWrite(Motor_left_back_direction, HIGH);
  analogWrite(Motor_left_back_speed, speed);
}

void Start_right(int speed)
{
  digitalWrite(Motor_right_front_direction, LOW);
  analogWrite(Motor_right_front_speed, speed);

  digitalWrite(Motor_right_back_direction, HIGH);
  analogWrite(Motor_right_back_speed, speed);

  digitalWrite(Motor_left_front_direction, HIGH);
  analogWrite(Motor_left_front_speed, speed);

  digitalWrite(Motor_left_back_direction, LOW);
  analogWrite(Motor_left_back_speed, speed);
}

void Backwards(int speed_right, int speed_left)
{
  digitalWrite(Motor_right_front_direction, LOW);
  analogWrite(Motor_right_front_speed, speed_right);

  digitalWrite(Motor_right_back_direction, HIGH);
  analogWrite(Motor_right_back_speed, speed_right);

  digitalWrite(Motor_left_front_direction, LOW);
  analogWrite(Motor_left_front_speed, speed_left);

  digitalWrite(Motor_left_back_direction, HIGH);
  analogWrite(Motor_left_back_speed, speed_left);
}

void Stop_Motors()
{
  digitalWrite(Motor_right_front_direction, LOW);
  analogWrite(Motor_right_front_speed, 0);

  digitalWrite(Motor_right_back_direction, LOW);
  analogWrite(Motor_right_back_speed, 0);

  digitalWrite(Motor_left_front_direction, LOW);
  analogWrite(Motor_left_front_speed, 0);

  digitalWrite(Motor_left_back_direction, LOW);
  analogWrite(Motor_left_back_speed, 0);
}

void turn_left(int speed)
{
  sensors_event_t turning_angle;
  Gyro.getEvent(&turning_angle);
  orientation_start = turning_angle.orientation.x;
  estimated_angle = orientation_start - 90;
  if(estimated_angle < 0)
  {
    estimated_angle = estimated_angle + 360;
  }
  if(estimated_angle >= start_east && estimated_angle < start_south)
  {
    estimated_direction = east;
  }
  else if(estimated_angle >= start_south && estimated_angle < start_west)
  {
    estimated_direction = south;
  }
  else if(estimated_angle >= start_west && estimated_angle < start_north)
  {
    estimated_direction = west;
  }
  else
  {
    estimated_direction = north;
  }
  Start_left(speed);
  Time_start_motors = millis();
  while(millis() - Time_start_motors < 3000)
  {
    sensors_event_t turning_angle;
    Gyro.getEvent(&turning_angle);
    orientation_value = turning_angle.orientation.x;
    Serial.println(turning_angle.orientation.x);
    if(orientation_value >= estimated_direction - 1 && orientation_value <= estimated_direction + 1)
    {
      break;
    }
    if(orientation_start - orientation_value >= 70)
    {
      Start_left(speed / 5);
    }
    delay(5);
  }
  Stop_Motors();
}

void turn_right(int speed)
{
  sensors_event_t turning_angle;
  Gyro.getEvent(&turning_angle);
  orientation_start = turning_angle.orientation.x;
  estimated_angle = orientation_start + 90;
  if(estimated_angle > 0)
  {
    estimated_angle = estimated_angle - 360;
  }
  if(estimated_angle >= start_east && estimated_angle < start_south)
  {
    estimated_direction = east;
  }
  else if(estimated_angle >= start_south && estimated_angle < start_west)
  {
    estimated_direction = south;
  }
  else if(estimated_angle >= start_west && estimated_angle < start_north)
  {
    estimated_direction = west;
  }
  else
  {
    estimated_direction = north;
  }
  Start_right(speed);
  Time_start_motors = millis();
  while(millis() - Time_start_motors < 3000)
  {
    sensors_event_t turning_angle;
    Gyro.getEvent(&turning_angle);
    orientation_value = turning_angle.orientation.x;
    if(orientation_value >= estimated_direction - 1 && orientation_value <= estimated_direction + 1)
    {
      break;
    }
    else if(orientation_start - orientation_value <= -70)
    {
      Start_right( speed / 5 );
    }
    delay(1);
  }
  Stop_Motors();
}

void turn_around(int speed)
{
  sensors_event_t turning_angle;
  Gyro.getEvent(&turning_angle);
  orientation_start = turning_angle.orientation.x;
    estimated_angle = orientation_start + 180;
  if(estimated_angle > 0)
  {
    estimated_angle = estimated_angle - 360;
  }
  if(estimated_angle >= start_east && estimated_angle < start_south)
  {
    estimated_direction = east;
  }
  else if(estimated_angle >= start_south && estimated_angle < start_west)
  {
    estimated_direction = south;
  }
  else if(estimated_angle >= start_west && estimated_angle < start_north)
  {
    estimated_direction = west;
  }
  else
  {
    estimated_direction = north;
  }
  Start_right(speed);
  Time_start_motors = millis();
  while(millis() - Time_start_motors < 6000)
  {
    sensors_event_t turning_angle;
    Gyro.getEvent(&turning_angle);
    orientation_value = turning_angle.orientation.x;
    if(orientation_value >= estimated_direction - 1 && orientation_value <= estimated_direction + 1)
    {
      break;
    } 
    else if(orientation_value - orientation_start >= 160)
    {
      Start_right(speed / 5);
    }
    delay(5);
  }
  Stop_Motors();
}

void Motors_Init()
{
  for(int i=3; i<9; i++){
    pinMode(i, OUTPUT);
  }
  for(int i=11; i<13; i++){
    pinMode(i, OUTPUT);
  }
}

void Gyro_Init()
{
  Gyro.begin();
  pinMode(Gyro_reset_pin , OUTPUT);
}

void reset_gyro()
{
  digitalWrite(Gyro_reset_pin, LOW);
  delay(10);
  digitalWrite(Gyro_reset_pin, HIGH);
}