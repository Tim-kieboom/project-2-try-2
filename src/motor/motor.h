#pragma once
#ifndef _MOTOR_H_
#define _MOTRO_H_

#define FORWARD         1
#define BACKWARD        2
#define TURN_LEFT       3
#define TURN_RIGHT      4
#define STOP_MOVING     5
#define WALL_DETECTED   6


#define MOTOR_OFF                   0
#define CLOCK_WISE                  1
#define COUNTER_CLOCK_WISE          2

#define MOTOR_A_PIN1                23
#define MOTOR_A_PIN2                25
#define MOTOR_B_PIN1                26
#define MOTOR_B_PIN2                27

//Eneble motor driver side A
#define ENA                         18
//Eneble motor driver side B
#define ENB                         19                     

void motorInnit();
void move(int mode, int speed);
void testMotor();

#endif