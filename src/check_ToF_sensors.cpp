
#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h>
#include <SPI.h>

#include "check_ToF_sensors.h"

#define distClear 200

#define offsetFrontRight -38
#define offsetFrontLeft -57
#define offsetRightFront -44
#define offsetLeftfront -58
#define offsetRightBack -45
#define offsetLeftBack -42
#define offsetBackRight -51
#define offsetBackLeft -48

int x=29;

bool front_clear;
bool right_clear;
bool back_clear;
bool left_clear;


VL53L0X Sensor_front_left;
VL53L0X Sensor_front_right;
VL53L0X Sensor_right_front;
VL53L0X Sensor_right_back;
VL53L0X Sensor_back_right;
VL53L0X Sensor_back_left;
VL53L0X Sensor_left_back;
VL53L0X Sensor_left_front;

void check_ToF_sensors_Init(){
  Serial.begin(9600);

  Wire.begin();

  for(int i=x; i<44; i=i+2)
  {
    pinMode(i , OUTPUT);
    digitalWrite(i , LOW);
  }

  Sensor_back_left.setTimeout(500);
  Sensor_back_right.setTimeout(500);
  Sensor_front_left.setTimeout(500);
  Sensor_front_right.setTimeout(500);
  Sensor_left_back.setTimeout(500);
  Sensor_left_front.setTimeout(500);
  Sensor_right_back.setTimeout(500);
  Sensor_right_front.setTimeout(500);

  digitalWrite(29, HIGH);
  delay(150);
  Sensor_left_back.init(true);
  delay(100);
  Sensor_left_back.setAddress((uint8_t)31);

  digitalWrite(31, HIGH);
  delay(150);
  Sensor_back_left.init(true);
  delay(100);
  Sensor_back_left.setAddress((uint8_t)32);

  digitalWrite(33, HIGH);
  delay(150);
  Sensor_front_left.init(true);
  delay(100);
  Sensor_front_left.setAddress((uint8_t)33);;

  digitalWrite(35, HIGH);
  delay(150);
  Sensor_left_front.init(true);
  delay(100);
  Sensor_left_front.setAddress((uint8_t)34);

  digitalWrite(37, HIGH);
  delay(150);
  Sensor_right_back.init(true);
  delay(100);
  Sensor_right_back.setAddress((uint8_t)35);

  digitalWrite(39, HIGH);
  delay(150);
  Sensor_back_right.init(true);
  delay(100);
  Sensor_back_right.setAddress((uint8_t)36);

  digitalWrite(41, HIGH);
  delay(150);
  Sensor_front_right.init(true);
  delay(100);
  Sensor_front_right.setAddress((uint8_t)37);

  digitalWrite(43, HIGH);
  delay(150);
  Sensor_right_front.init(true);
  delay(100);
  Sensor_right_front.setAddress((uint8_t)38);


  Sensor_front_left.startContinuous();
  Sensor_front_right.startContinuous();
  Sensor_right_front.startContinuous();
  Sensor_right_back.startContinuous();
  Sensor_back_right.startContinuous();
  Sensor_back_left.startContinuous();
  Sensor_left_back.startContinuous();
  Sensor_left_front.startContinuous();
}


void check_surroundings()
{
  if(distanceFrontRight()> distClear)
  {
    front_clear = true;
  }
  else
  {
    front_clear = false;
  }

  if(distanceRightBack() > distClear)
  {
    right_clear = true;
  }
  else
  {
    right_clear = false;
  }

  if(distanceBackLeft() > distClear)
  {
    back_clear = true;
  }
  else
  {
    back_clear = false;
  }

  if(distanceLeftBack() > distClear)
  {
    left_clear = true;
  }
  else
  {
    left_clear = false;
  }
}


void showDistances()
{
  Serial.print("Vorne Links: " );
  Serial.println(distanceFrontLeft());

  Serial.print("Vorne Rechts: ");
  Serial.println(distanceFrontRight());
  
  Serial.print("Links Vorne: ");
  Serial.println(distanceLeftFront());
  
  Serial.print("Rechts Vorne: ");
  Serial.println(distanceRightFront());
  
  Serial.print("Links Hinten: ");
  Serial.println(distanceLeftBack());
  
  Serial.print("Rechts Hinten: ");
  Serial.println(distanceRightBack());
  
  Serial.print("Hinten Links: ");
  Serial.println(distanceBackLeft());
  
  Serial.print("Hinten Rechts: ");
  Serial.println(distanceBackRight());
}


int distanceFrontLeft()
{
  return(Sensor_front_left.readRangeContinuousMillimeters() + offsetFrontLeft);
}

int distanceFrontRight()
{
  return(Sensor_front_right.readRangeContinuousMillimeters() + offsetFrontRight);
}

int distanceLeftFront()
{
  return(Sensor_left_front.readRangeContinuousMillimeters() + offsetLeftfront);
}

int distanceRightFront()
{
  return(Sensor_right_front.readRangeContinuousMillimeters() + offsetRightFront);
}

int distanceLeftBack()
{
  return(Sensor_left_back.readRangeContinuousMillimeters() + offsetLeftBack);
}

int distanceRightBack()
{
  return(Sensor_right_back.readRangeContinuousMillimeters() + offsetRightBack);
}

int distanceBackLeft()
{
  return(Sensor_back_left.readRangeContinuousMillimeters() + offsetBackLeft);
}

int distanceBackRight()
{
  return(Sensor_back_right.readRangeContinuousMillimeters() + offsetBackRight);
}