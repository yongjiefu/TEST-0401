#ifndef __PID_H__
#define __PID_H__

#include "stm32f10x.h"
#include "sys.h"

typedef struct
{
	 //����ٶ�PID����
	float Velcity_Kp;
	float Velcity_Ki;
	float Velcity_Kd;
	float Ur;				//�޷�ֵ	
	u8 PID_is_Enable;		//PIDʹ��
	int Un;					//�������ֵ
	int En_1;				//��һ�ε����ֵ
	int En_2;				//���ϴε����ֵ
	int PWM;				//���PWMֵ
    
     //����ٶ�PID����
	float Velcity_Kp_1;
	float Velcity_Ki_1;
	float Velcity_Kd_1;
	float Ur_1;				//�޷�ֵ	
	u8 PID_is_Enable_1;		//PIDʹ��
	int Un_1;					//�������ֵ
	int En_1_1;				//��һ�ε����ֵ
	int En_2_1;				//���ϴε����ֵ
	int PWM_1;				//���PWMֵ
	
    //����ٶ�PID����
	float Velcity_Kp_2;
	float Velcity_Ki_2;
	float Velcity_Kd_2;
	float Ur_2;				//�޷�ֵ	
	u8 PID_is_Enable_2;		//PIDʹ��
	int Un_2;					//�������ֵ
	int En_1_2;				//��һ�ε����ֵ
	int En_2_2;				//���ϴε����ֵ
	int PWM_2;				//���PWMֵ
    
    //����ٶ�PID����
	float Velcity_Kp_3;
	float Velcity_Ki_3;
	float Velcity_Kd_3;
	float Ur_3;				//�޷�ֵ	
	u8 PID_is_Enable_3;		//PIDʹ��
	int Un_3;					//�������ֵ
	int En_1_3;				//��һ�ε����ֵ
	int En_2_3;				//���ϴε����ֵ
	int PWM_3;				//���PWMֵ
    
    //����ٶ�PID����
	float Velcity_Kp_4;
	float Velcity_Ki_4;
	float Velcity_Kd_4;
	float Ur_4;				//�޷�ֵ	
	u8 PID_is_Enable_4;		//PIDʹ��
	int Un_4;					//�������ֵ
	int En_1_4;				//��һ�ε����ֵ
	int En_2_4;				//���ϴε����ֵ
	int PWM_4;				//���PWMֵ
}PID_InitDefStruct;

void PID_Init(PID_InitDefStruct* p);
void Velocity_PID(unsigned char channel,int TargetVelocity,int CurrentVelocity,PID_InitDefStruct* p);

#endif



