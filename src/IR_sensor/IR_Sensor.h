#pragma once
#ifndef _IR_SENSOR_H_
#define _IR_SENSOR_H_

#define FORWARD         1
#define BACKWARD        2
#define LEFT            3
#define RIGHT           4
#define STOP_MOVING     5
#define WALL_DETECTED   6

#define SENTINEL_VALUE -1


void IR_Innit();
int* checkIR();
void printIR_Data();

#endif