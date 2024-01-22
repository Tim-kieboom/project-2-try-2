#pragma once
#ifndef _MOTOR_H_
#define _MOTRO_H_

#define FORWARD         0
#define BACKWARD        3
#define LEFT            1
#define RIGHT           2
#define STOP_MOVING     4
#define WALL_DETECTED   5


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

#endif