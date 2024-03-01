#pragma once
#ifndef _MOTOR_H_
#define _MOTRO_H_

#include "./Timer/Timer.h"

#define FORWARD         1
#define BACKWARD        2
#define LEFT            3
#define RIGHT           4
#define STOP_MOVING     5
#define WALL_DETECTED   6


#define MOTOR_OFF                   0
#define CLOCK_WISE                  1
#define COUNTER_CLOCK_WISE          2

#define MOTOR_A_PIN1                15 //a8
#define MOTOR_A_PIN2                33 //a9
#define MOTOR_A                     true

#define MOTOR_B_PIN1                27 //a10
#define MOTOR_B_PIN2                12 //a11
#define MOTOR_B                     false


//Eneble motor driver side A
#define ENA                         13
//Eneble motor driver side B
#define ENB                         32                     

void motorInnit();
void moveCar(uint8_t mode);
void testMotor();
void motorPWM(int cyle_us);

/*
moveAndWait_ms(uint8_t move , uint32_t time_ms) = moves in direction 'move' for 'time_ms' (returns true if end of move
    -move    = what direction to move in (BACKWARD, LEFT etc..)
    -time_ms = how long the move should take in milliseconds

moveAndWait_ms(uint8_t* moveArray, uint32_t* timeArray_ms) = a sequence of moves with each there time_ms (timeArray_ms.size() must be >= moveArray.size())
*/
bool moveAndWait_ms(uint8_t move , uint32_t time_ms);
bool moveAndWait_ms(uint8_t* moveArray, uint32_t* timeArray_ms, uint8_t size);

#endif