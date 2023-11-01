#pragma once

extern void Forward(int speed_right, int speed_left);

extern void Start_left(int speed);

extern void Start_right(int speed);

extern void Backwards(int speed_right, int speed_left);

extern void Stop_Motors();

extern void turn_right(int speed);

extern void turn_left(int speed);

extern void turn_around(int speed);

extern void Motors_Init();

extern void Gyro_Init();