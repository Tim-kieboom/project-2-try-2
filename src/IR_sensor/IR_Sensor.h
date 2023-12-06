#pragma once
#ifndef _IR_SENSOR_H_
#define _IR_SENSOR_H_

#define FORWARD         1
#define BACKWARD        2
#define TURN_LEFT       3
#define TURN_RIGHT      4
#define STOP_MOVING     5
#define WALL_DETECTED   6

void IR_Innit();
int checkIR();

#endif