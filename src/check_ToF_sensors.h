#pragma once

extern bool front_clear;
extern bool right_clear;
extern bool back_clear;
extern bool left_clear;


extern void check_ToF_sensors_Init();

extern void check_surroundings();

extern void showDistances();

extern int distanceFrontLeft();
extern int distanceFrontRight();
extern int distanceLeftFront();
extern int distanceRightFront();
extern int distanceLeftBack();
extern int distanceRightBack();
extern int distanceBackLeft();
extern int distanceBackRight();