#pragma once
#ifndef _IR_SENSOR_H_
#define _IR_SENSOR_H_

#define FORWARD         0
#define BACKWARD        1
#define TURN_LEFT       2
#define TURN_RIGHT      3
#define STOP_MOVING     4
#define WALL_DETECTED   5

#define SENTINEL_VALUE -1


void IR_Innit();
int* checkIR();
void printIR_Data();

#endif