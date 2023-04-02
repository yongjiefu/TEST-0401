#ifndef __PID_H__
#define __PID_H__

#include "stm32f10x.h"
#include "sys.h"

typedef struct
{
	 //相关速度PID参数
	float Velcity_Kp;
	float Velcity_Ki;
	float Velcity_Kd;
	float Ur;				//限幅值	
	u8 PID_is_Enable;		//PID使能
	int Un;					//期望输出值
	int En_1;				//上一次的误差值
	int En_2;				//上上次的误差值
	int PWM;				//输出PWM值
    
     //相关速度PID参数
	float Velcity_Kp_1;
	float Velcity_Ki_1;
	float Velcity_Kd_1;
	float Ur_1;				//限幅值	
	u8 PID_is_Enable_1;		//PID使能
	int Un_1;					//期望输出值
	int En_1_1;				//上一次的误差值
	int En_2_1;				//上上次的误差值
	int PWM_1;				//输出PWM值
	
    //相关速度PID参数
	float Velcity_Kp_2;
	float Velcity_Ki_2;
	float Velcity_Kd_2;
	float Ur_2;				//限幅值	
	u8 PID_is_Enable_2;		//PID使能
	int Un_2;					//期望输出值
	int En_1_2;				//上一次的误差值
	int En_2_2;				//上上次的误差值
	int PWM_2;				//输出PWM值
    
    //相关速度PID参数
	float Velcity_Kp_3;
	float Velcity_Ki_3;
	float Velcity_Kd_3;
	float Ur_3;				//限幅值	
	u8 PID_is_Enable_3;		//PID使能
	int Un_3;					//期望输出值
	int En_1_3;				//上一次的误差值
	int En_2_3;				//上上次的误差值
	int PWM_3;				//输出PWM值
    
    //相关速度PID参数
	float Velcity_Kp_4;
	float Velcity_Ki_4;
	float Velcity_Kd_4;
	float Ur_4;				//限幅值	
	u8 PID_is_Enable_4;		//PID使能
	int Un_4;					//期望输出值
	int En_1_4;				//上一次的误差值
	int En_2_4;				//上上次的误差值
	int PWM_4;				//输出PWM值
}PID_InitDefStruct;

void PID_Init(PID_InitDefStruct* p);
void Velocity_PID(unsigned char channel,int TargetVelocity,int CurrentVelocity,PID_InitDefStruct* p);

#endif



