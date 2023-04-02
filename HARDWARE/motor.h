#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f10x.h"
#include "math.h"
#include "stdlib.h" 
#include "delay.h"
#include "pid.h"
#include "vofa.h"
extern unsigned int PWM_SPEED;
extern unsigned int speed_flag;
extern unsigned int CodedData_PC0_1;
extern unsigned int CodedData_PC2_1;
extern unsigned int CodedData_PC4_1;
extern unsigned int CodedData_PC10_1;

extern PID_InitDefStruct PID_Struct;
extern float RPM_1;
extern float RPM_2;
extern float RPM_3;
extern float RPM_4;

void MOTOR_Init(void);
void PWM_MOTOR_Init_TIM8(void);
void PWM_MOTOR_Init_TIM3(void);
void EXTI_MOTOR_Init(void);
void MOTOR_PWM_Set(unsigned int channel, unsigned int freq,unsigned int duty);
void MotorSpeedSet(unsigned int channel, int speed);

void Car_Stop(void);
void Car_Go(unsigned int speed,unsigned int distance);
void Car_Back(unsigned int speed,unsigned int distance);
void Car_Left(unsigned int speed,unsigned int angle);
void Car_Right(unsigned int speed,unsigned int angle);
void Car_Go_PID(unsigned int TargetCoded,unsigned int distance);

#endif

