#pragma once
#ifndef _MOTOR_H_
#define _MOTRO_H_

#define FORWARD         1
#define BACKWARD        2
#define TURN_LEFT       3
#define TURN_RIGHT      4
#define STOP_MOVING     5
#define WALL_DETECTED   6

#define MOTOR_A_PIN1                5 
#define MOTOR_A_PIN2                6
#define MOTOR_B_PIN1                10
#define MOTOR_B_PIN2                9

void motorInnit();
void move(int mode);
void testMotor();

#endif