#pragma once
#ifndef _MOTOR_H_
#define _MOTRO_H_

#define FORWARD         0
#define BACKWARD        1
#define LEFT            2
#define RIGHT           3
#define STOP_MOVING     4
#define WALL_DETECTED   5


#define MOTOR_OFF                   0
#define CLOCK_WISE                  1
#define COUNTER_CLOCK_WISE          2

#define MOTOR_A_PIN1                23
#define MOTOR_A_PIN2                25
#define MOTOR_A                     true

#define MOTOR_B_PIN1                26
#define MOTOR_B_PIN2                27
#define MOTOR_B                     false


//Eneble motor driver side A
#define ENA                         18
//Eneble motor driver side B
#define ENB                         19                     

void motorInnit();
void moveCar(uint8_t mode);
void testMotor();

#endif