#include "motor.h"

void MOTOR_Init(void)
{
    PWM_MOTOR_Init_TIM3();
    PWM_MOTOR_Init_TIM8();
    EXTI_MOTOR_Init();  
}
void PWM_MOTOR_Init_TIM8(void)
{
   	GPIO_InitTypeDef 		GPIO_InitStructure;
	TIM_OCInitTypeDef		TIMOC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_InitStructure;
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);			//GPIOC
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);			//时钟使能
		
	GPIO_InitStructure.GPIO_Pin   		= GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode  		= GPIO_Mode_AF_PP;			//复用推挽输出
	GPIO_InitStructure.GPIO_Speed		= GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
		
	TIM_InitStructure.TIM_Period	 	= 9;
	TIM_InitStructure.TIM_Prescaler 	= 7199;	
	TIM_InitStructure.TIM_ClockDivision	= TIM_CKD_DIV1;				//设置时钟分割TDTS = Tck_tim
	TIM_InitStructure.TIM_CounterMode 	= TIM_CounterMode_Up;		//向上计数
	TIM_TimeBaseInit(TIM8,&TIM_InitStructure);
	
	TIMOC_InitStructure.TIM_OCMode		= TIM_OCMode_PWM2;			//选择定时器模式:TIM脉冲宽度调制模式2
	TIMOC_InitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIMOC_InitStructure.TIM_OCPolarity	= TIM_OCPolarity_Low;
    /**一定要加**/
    TIMOC_InitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset ;
    TIMOC_InitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
    TIMOC_InitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
    
	TIM_OC1Init(TIM8, &TIMOC_InitStructure);						//根据T指定的参数初始化外设TIM8 OC1
	TIM_OC2Init(TIM8, &TIMOC_InitStructure);						//根据T指定的参数初始化外设TIM8 OC2
	TIM_OC3Init(TIM8, &TIMOC_InitStructure);						//根据T指定的参数初始化外设TIM8 OC3
	TIM_OC4Init(TIM8, &TIMOC_InitStructure);						//根据T指定的参数初始化外设TIM8 OC4
	
	TIM_OC1PreloadConfig(TIM8,TIM_OCPreload_Enable);				//使能TIM8在CCR1上的预装载寄存器 
	TIM_OC2PreloadConfig(TIM8,TIM_OCPreload_Enable);				//使能TIM8在CCR2上的预装载寄存器 
	TIM_OC3PreloadConfig(TIM8,TIM_OCPreload_Enable);				//使能TIM8在CCR3上的预装载寄存器 
	TIM_OC4PreloadConfig(TIM8,TIM_OCPreload_Enable);				//使能TIM8在CCR4上的预装载寄存器 

	TIM_CtrlPWMOutputs(TIM8,ENABLE);
    TIM_ARRPreloadConfig(TIM8,ENABLE);      //TIM3在APR上预装载寄存器使能
	TIM_Cmd(TIM8,ENABLE);											//使能TIM8
    
    
    
}
void PWM_MOTOR_Init_TIM3(void)
{   
    //当没有重映射时，TIM3的四个通道CH1，CH2，CH3，CH4分别对应PA6，PA7,PB0,PB1
    //当部分重映射时，TIM3的四个通道CH1，CH2，CH3，CH4分别对应PB4，PB5,PB0,PB1
    //当完全重映射时，TIM3的四个通道CH1，CH2，CH3，CH4分别对应PC6，PC7,PC8,PC9	
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);                            //使能定时器3时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB , ENABLE);    //使能GPIO时钟
    
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1 | GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //初始化TIM3
    TIM_TimeBaseInitStructure.TIM_Period        = 9;
    TIM_TimeBaseInitStructure.TIM_Prescaler     = 7199;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);

    //初始化TIM3_CH1  PWM 模式
    TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High;
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);

    //初始化TIM3_CH2  PWM 模式
    TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High;
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);

    //初始化TIM3_CH3  PWM 模式
    TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High;
    TIM_OC3Init(TIM3, &TIM_OCInitStructure);

    //初始化TIM3_CH4  PWM 模式
    TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High;
    TIM_OC4Init(TIM3, &TIM_OCInitStructure);

    //使能TIM3在CCR上的预装载寄存器
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

    //使能TIM3
    TIM_CtrlPWMOutputs(TIM3,ENABLE);
    TIM_ARRPreloadConfig(TIM3,ENABLE);      //TIM3在APR上预装载寄存器使能
    TIM_Cmd(TIM3, ENABLE);
}
void EXTI_MOTOR_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;          //下拉输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOC, &GPIO_InitStructure);

  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource0);
  	EXTI_InitStructure.EXTI_Line	= EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 
    
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource2);
    EXTI_InitStructure.EXTI_Line	= EXTI_Line2;
    EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt;	
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上降沿触发
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);	

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource4);
    EXTI_InitStructure.EXTI_Line	= EXTI_Line4;
    EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt;	
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上降沿触发
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);	

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource10);
    EXTI_InitStructure.EXTI_Line	= EXTI_Line10;
    EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt;	
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上降沿触发
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);		

  	NVIC_InitStructure.NVIC_IRQChannel 					 = EXTI0_IRQn;			
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 0;				
  	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;							
  	NVIC_Init(&NVIC_InitStructure); 
    
    NVIC_InitStructure.NVIC_IRQChannel 					 = EXTI2_IRQn;			
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 1;				
  	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;							
  	NVIC_Init(&NVIC_InitStructure); 
    
    NVIC_InitStructure.NVIC_IRQChannel 					 = EXTI4_IRQn;			
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 2;				
  	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;							
  	NVIC_Init(&NVIC_InitStructure); 
    
    NVIC_InitStructure.NVIC_IRQChannel 					 = EXTI15_10_IRQn;			
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 3;				
  	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;							
  	NVIC_Init(&NVIC_InitStructure); 	
}

void MOTOR_PWM_Set(unsigned int channel, unsigned int freq,unsigned int duty)
{	  
    freq = 10000 / freq;
    duty = freq * duty / 100;
    
    TIM3->ARR = freq;
    TIM8->ARR = freq;	
    
	switch(channel){
        case 1:                       
            TIM3->CCR1 = duty;
        break;
        case 2:           
            TIM3->CCR2 = duty;
        break;
        case 3:
            TIM3->CCR3 = duty;
        break;
        case 4:
            TIM3->CCR4 = duty;
            //TIM_SetCompare4(TIM3,duty);
        break;
		case 5:		
			TIM8->CCR1 = duty;
		break;
		case 6:	                   
			TIM8->CCR2 = duty;
		break;
		case 7:	                  
			TIM8->CCR3 = duty;
		break;
		case 8:		            
			TIM8->CCR4 = duty;
		break;       
	}
}

void MotorSpeedSet(unsigned int channel,int speed)
{   
    unsigned int freq = 2000;
    switch(channel){    //电机选择
        case 1:         //一号电机
            if(speed == 0){
                
                MOTOR_PWM_Set(1,freq,0);
                MOTOR_PWM_Set(2,freq,0);
            } 
            if(speed > 0){
                MOTOR_PWM_Set(1,freq,speed);
                MOTOR_PWM_Set(2,freq,0);           
            }else if(speed < 0){
                speed = abs(speed);
                MOTOR_PWM_Set(1,freq,0);
                MOTOR_PWM_Set(2,freq,speed);                
            }   
        break; 
        case 2:         //二号电机
            if(speed == 0){                
                MOTOR_PWM_Set(3,freq,0);
                MOTOR_PWM_Set(4,freq,0);
            } 
            if(speed > 0){
                MOTOR_PWM_Set(4,freq,speed);
                MOTOR_PWM_Set(3,freq,0);           
            }else if(speed < 0){
                speed = abs(speed);
                MOTOR_PWM_Set(4,freq,0);
                MOTOR_PWM_Set(3,freq,speed);                
            }   
        break;
        case 3:         //三号电机
            if(speed == 0){                
                MOTOR_PWM_Set(5,freq,0);
                MOTOR_PWM_Set(6,freq,0);
            } 
            if(speed > 0){
                MOTOR_PWM_Set(6,freq,speed);
                MOTOR_PWM_Set(5,freq,0);           
            }else if(speed < 0){
                speed = abs(speed);
                MOTOR_PWM_Set(6,freq,0);
                MOTOR_PWM_Set(5,freq,speed);                
            }   
        break;
        case 4:         //四号电机
            if(speed == 0){                
                MOTOR_PWM_Set(7,freq,0);
                MOTOR_PWM_Set(8,freq,0);
            } 
            if(speed > 0){
                MOTOR_PWM_Set(7,freq,speed);
                MOTOR_PWM_Set(8,freq,0);           
            }else if(speed < 0){
                speed = abs(speed);
                MOTOR_PWM_Set(7,freq,0);
                MOTOR_PWM_Set(8,freq,speed);                
            }   
        break;
    }  
}
void Car_Stop(void)
{
    MotorSpeedSet(1,0);
    MotorSpeedSet(2,0);
    MotorSpeedSet(3,0);
    MotorSpeedSet(4,0);
}
void Car_Go(unsigned int speed,unsigned int distance)
{    
    distance = distance * 15.7; 
    do{
        MotorSpeedSet(1,speed);
        MotorSpeedSet(2,speed);
        MotorSpeedSet(3,speed);
        MotorSpeedSet(4,speed); 
    }  
    while((CodedData_PC0_1 < distance)&&(CodedData_PC2_1 < distance)&&(CodedData_PC4_1 < distance)&&(CodedData_PC10_1 < distance));
    CodedData_PC0_1 = 0;
    CodedData_PC2_1 = 0;
    CodedData_PC4_1 = 0;
    CodedData_PC10_1 = 0;
    Car_Stop();
}
void Car_Back(unsigned int speed,unsigned int distance)
{
    distance = distance * 15.7;
    speed = speed * -1;
    do{
        MotorSpeedSet(1,speed);
        MotorSpeedSet(2,speed);
        MotorSpeedSet(3,speed);
        MotorSpeedSet(4,speed);
    }
    while((CodedData_PC0_1 < distance)&&(CodedData_PC2_1 < distance)&&(CodedData_PC4_1 < distance)&&(CodedData_PC10_1 < distance));
    CodedData_PC0_1 = 0;
    CodedData_PC2_1 = 0;
    CodedData_PC4_1 = 0;
    CodedData_PC10_1 = 0;
    Car_Stop();
}
void Car_Left(unsigned int speed,unsigned int angle)
{
    do{
        MotorSpeedSet(1,speed * -1.0);
        MotorSpeedSet(2,speed);
        MotorSpeedSet(3,speed);
        MotorSpeedSet(4,speed * -1.0);  
    }
    while((CodedData_PC0_1 < angle)&&(CodedData_PC2_1 < angle)&&(CodedData_PC4_1 < angle)&&(CodedData_PC10_1 < angle));
    CodedData_PC0_1 = 0;
    CodedData_PC2_1 = 0;
    CodedData_PC4_1 = 0;
    CodedData_PC10_1 = 0;
    Car_Stop();
}
void Car_Right(unsigned int speed,unsigned int angle)
{
    do{
        MotorSpeedSet(1,speed);
        MotorSpeedSet(2,speed * -1.0);
        MotorSpeedSet(3,speed * -1.0);
        MotorSpeedSet(4,speed); 
    }
    while((CodedData_PC0_1 < angle)&&(CodedData_PC2_1 < angle)&&(CodedData_PC4_1 < angle)&&(CodedData_PC10_1 < angle));
    CodedData_PC0_1 = 0;
    CodedData_PC2_1 = 0;
    CodedData_PC4_1 = 0;
    CodedData_PC10_1 = 0;
    Car_Stop();
}
void Car_Go_PID(unsigned int TargetCoded,unsigned int distance)
{  
    distance = distance * 15.7; 

    do{        
        MotorSpeedSet(1,PID_Struct.PWM_1);
        MotorSpeedSet(2,PID_Struct.PWM_2);
        MotorSpeedSet(3,PID_Struct.PWM_3);
        MotorSpeedSet(4,PID_Struct.PWM_4);
        Velocity_PID(1,TargetCoded,RPM_1,&PID_Struct);
        Velocity_PID(2,TargetCoded,RPM_2,&PID_Struct);
        Velocity_PID(3,TargetCoded,RPM_3,&PID_Struct);
        Velocity_PID(4,TargetCoded,RPM_4,&PID_Struct);
        vofa_send(RPM_1,RPM_2,RPM_3,RPM_4);        
    }
    while((CodedData_PC0_1 < distance)&&(CodedData_PC2_1 < distance)&&(CodedData_PC4_1 < distance)&&(CodedData_PC10_1 < distance));
    CodedData_PC0_1 = 0;
    CodedData_PC2_1 = 0;
    CodedData_PC4_1 = 0;
    CodedData_PC10_1 = 0;
    Car_Stop();
}


