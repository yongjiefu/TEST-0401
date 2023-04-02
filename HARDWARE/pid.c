#include "pid.h"

/**************************************************************************
���ܣ�PID�ṹ���ʼ��
������void PID_Init(PID_InitDefStruct* p)
���ڣ�2022.02.18
������p:PID�ṹ�壨��ַ��
**************************************************************************/
void PID_Init(PID_InitDefStruct* p)
{
//    p->Velcity_Kp = 0.1008;
//	p->Velcity_Ki = 0.003;
//    p->Velcity_Kd = 0.0015;
//	p->Ur = 100;
//	p->PID_is_Enable = 1;
//	p->Un = 0;
//	p->En_1 = 0;
//	p->En_2 = 0;
//	p->PWM = 0;
    
    p->Velcity_Kp_1    = 5.0;
    p->Velcity_Ki_1    = 0.001;
    p->Velcity_Kd_1    = 0;
    p->Ur_1            = 100;
    p->PID_is_Enable_1 = 1;
    p->Un_1            = 0;
    p->En_1_1          = 0;
    p->En_2_1          = 0;
    p->PWM_1           = 0;
    
    p->Velcity_Kp_2    = 5.0;
    p->Velcity_Ki_2    = 0.001;
    p->Velcity_Kd_2    = 0;
    p->Ur_2            = 100;
    p->PID_is_Enable_2 = 1;
    p->Un_2            = 0;
    p->En_1_2          = 0;
    p->En_2_2          = 0;
    p->PWM_2           = 0;
    
    p->Velcity_Kp_3    = 5.0;
    p->Velcity_Ki_3    = 0.001;
    p->Velcity_Kd_3    = 0;
    p->Ur_3            = 100;
    p->PID_is_Enable_3 = 1;
    p->Un_3            = 0;
    p->En_1_3          = 0;
    p->En_2_3          = 0;
    p->PWM_3           = 0;
    
    p->Velcity_Kp_4    = 5.0;
    p->Velcity_Ki_4    = 0.001;
    p->Velcity_Kd_4    = 0;
    p->Ur_4            = 100;
    p->PID_is_Enable_4 = 1;
    p->Un_4            = 0;
    p->En_1_4          = 0;
    p->En_2_4          = 0;
    p->PWM_4           = 0;
}

/**************************************************************************
���ܣ�PID�����㷨�������PWM��ֵ��PID�ṹ���PWM
������void Velocity_PID(int TargetVelocity,int CurrentVelocity,PID_InitDefStruct* p)
���ڣ�2022.02.18
������TargetVelocity:�����ٶ��ٶ�  CurrentVelocity:ʵ���ٶ�  p:PID�ṹ�壨��ַ��
**************************************************************************/

void Velocity_PID(unsigned char channel,int TargetVelocity,int CurrentVelocity,PID_InitDefStruct* p)
{
//	if(p->PID_is_Enable == 1)
//	{
//		int En = TargetVelocity - CurrentVelocity;//���ֵ                                                     
//	
//		p->Un += p->Velcity_Kp*(En - p->En_1) + p->Velcity_Ki*En + p->Velcity_Kd*(En - 2*p->En_1 + p->En_2);//����ʽPID
//		
//		p->En_2=p->En_1;
//		p->En_1=En;
//		
//		p->PWM = p->Un/10.92;
//        //p->PWM = p->Un+58;
//        
//		/*����޷�*/
//		if(p->PWM>120) p->PWM  = 120;
//		if(p->PWM<25)  p->PWM   = 30;
//	}
//	else
//	{
//		PID_Init(p);
//	}

    switch(channel){
        case 1:
            if(p->PID_is_Enable_1 == 1){   
                int En_1 = TargetVelocity - CurrentVelocity;//���ֵ                                                     

                p->Un_1   += p->Velcity_Kp_1 * (En_1 - p->En_1_1) + p->Velcity_Ki_1*En_1 + p->Velcity_Kd_1*(En_1 - 2*p->En_1_1 + p->En_2_1);//����ʽPID
                p->En_2_1  = p->En_1_1;
                p->En_1_1  = En_1;
                p->PWM_1   = p->Un_1/10.92;

                /*����޷�*/
                if(p->PWM_1>120) p->PWM_1  = 120;   //PWM����������
                if(p->PWM_1<40)  p->PWM_1  = 40;    //PWM�����С����
            }
            else{   
                PID_Init(p);
            }             
        break;
        case 2:
            if(p->PID_is_Enable_2 == 1){   
                int En_2 = TargetVelocity - CurrentVelocity;//���ֵ                                                     

                p->Un_2   += p->Velcity_Kp_2 * (En_2 - p->En_1_2) + p->Velcity_Ki_2*En_2 + p->Velcity_Kd_2*(En_2 - 2*p->En_1_2 + p->En_2_2);//����ʽPID
                p->En_2_2  = p->En_1_2;
                p->En_1_2  = En_2;
                p->PWM_2   = p->Un_2/10.92;

                /*����޷�*/
                if(p->PWM_2>120) p->PWM_2  = 120;   //PWM����������
                if(p->PWM_2<40)  p->PWM_2  = 40;    //PWM�����С����
            }
            else{   
                PID_Init(p);
            }
        break;
        case 3:
            if(p->PID_is_Enable_3 == 1){   
                int En_3 = TargetVelocity - CurrentVelocity;//���ֵ                                                     

                p->Un_3   += p->Velcity_Kp_3 * (En_3 - p->En_1_3) + p->Velcity_Ki_3*En_3 + p->Velcity_Kd_3*(En_3 - 2*p->En_1_3 + p->En_2_3);//����ʽPID
                p->En_2_3  = p->En_1_3;
                p->En_1_3  = En_3;
                p->PWM_3   = p->Un_3/10.92;

                /*����޷�*/
                if(p->PWM_3>120) p->PWM_3  = 120;   //PWM����������
                if(p->PWM_3<40)  p->PWM_3  = 40;    //PWM�����С����
            }
            else{   
                PID_Init(p);
            }
        break;
        case 4:
            if(p->PID_is_Enable_4 == 1){   
                int En_4 = TargetVelocity - CurrentVelocity;//���ֵ                                                     

                p->Un_4   += p->Velcity_Kp_4 * (En_4 - p->En_1_4) + p->Velcity_Ki_4*En_4 + p->Velcity_Kd_4*(En_4 - 2*p->En_1_4 + p->En_2_4);//����ʽPID
                p->En_2_4  = p->En_1_4;
                p->En_1_4  = En_4;
                p->PWM_4   = p->Un_4/10.92;

                /*����޷�*/
                if(p->PWM_4>120) p->PWM_4  = 120;   //PWM����������
                if(p->PWM_4<40)  p->PWM_4  = 40;    //PWM�����С����
            }
            else{   
                PID_Init(p);
            }
        break;
    }    	
}


