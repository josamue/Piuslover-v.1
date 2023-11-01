#include <Arduino.h>
#include <SPI.h> 

#include "check_ToF_sensors.h"
#include "motors.h"
#include "one_tile.h"
#include "check_colorsensor.h"
#include "balance_out.h"

int check = 0;

void setup()
{
  Serial.begin(9600);
  Motors_Init();
  check_ToF_sensors_Init();
  Gyro_Init();
}

void loop()
{
  // showDistances();
  // delay(2000);
  Serial.println("Right_Clear: ");
  Serial.println(right_clear);

  check_surroundings();
  // check_color();
  // if(blue)
  // {
  //   delay(5000);
  // }
  // if(right_clear)
  // {
  //   Serial.println("rechts");
  //   turn_right(255);
  //   one_tile_forward(255,255);
  //   if(back_in_black)
  //   {
  //     black_tile();
  //   }
  // }
  // else if(front_clear)
  // {
  //   one_tile_forward(255,255);
  //   if(back_in_black)
  //   {
  //     black_tile();
  //   }
  // }
  // else if(left_clear)
  // {
  //   turn_left(255);
  //   one_tile_forward(255, 255);
  //   if(back_in_black)
  //   {
  //     black_tile();
  //   }
  // }
  // else
  // {
  //   turn_around(255);
  //   one_tile_forward(255, 255);
  // }

  // Serial.println("Links");
  // Serial.println(left_clear);
  // Serial.println("Rechts");
  // Serial.println(right_clear);
  // Serial.println("Hinten");
  // Serial.println(back_clear);
  // Serial.println("Vorne");
  // Serial.println(front_clear);
  // delay(1000);
  
}
