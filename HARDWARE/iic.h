#ifndef __IIC_H
#define __IIC_H	 

#include "sys.h"
#include "delay.h"


#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����


/* ����I2C�������ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����4�д��뼴������ı�SCL��SDA������ */

#define	IIC_SCK_PIN		GPIO_Pin_6						/* ���ӵ�SCKʱ���ߵ�GPIO */
#define IIC_SCK_PORT	GPIOB									/* GPIO�˿� */
#define IIC_SCK_CLK		RCC_APB2Periph_GPIOB	/* GPIO�˿�ʱ�� */
#define IIC_SCL    		PBout(6)							//SCL

#define	IIC_SDA_PIN		GPIO_Pin_7						/* ���ӵ�SDAʱ���ߵ�GPIO */
#define IIC_SDA_PORT	GPIOB									/* GPIO�˿� */
#define IIC_SDA_CLK		RCC_APB2Periph_GPIOB	/* GPIO�˿�ʱ�� */
#define IIC_SDA    		PBout(7)							//SDA
#define READ_SDA   		PBin(7)								//����SDA


/* �����дSCL��SDA�ĺ꣬�����Ӵ���Ŀ���ֲ�ԺͿ��Ķ��� */
#if 0		/* �������룺 1 ѡ��GPIO�Ŀ⺯��ʵ��IO��д */
	#define I2C_SCK_1()  GPIO_SetBits(IIC_SCK_PORT,IIC_SCK_PIN)			/* SCL = 1 */
	#define I2C_SCK_0()  GPIO_ResetBits(IIC_SCK_PORT,IIC_SCK_PIN)		/* SCL = 0 */
	
	#define I2C_SDA_1()  GPIO_SetBits(IIC_SDA_PORT,IIC_SDA_PIN)			/* SDA = 1 */
	#define I2C_SDA_0()  GPIO_ResetBits(IIC_SDA_PORT,IIC_SDA_PIN)		/* SDA = 0 */
	
	#define I2C_SDA_READ()  GPIO_ReadInputDataBit(GPIO_PORT_I2C,I2C_SDA_PIN)	/* ��SDA����״̬ */
#else	/* �����֧ѡ��ֱ�ӼĴ�������ʵ��IO��д */
	/*��ע�⣺����д������IAR��߼����Ż�ʱ���ᱻ�����������Ż� */
	#define I2C_SCK_1()  IIC_SCK_PORT->BSRR = IIC_SCK_PIN				/* SCL = 1 */
	#define I2C_SCK_0()  IIC_SCK_PORT->BRR = IIC_SCK_PIN				/* SCL = 0 */
	
	#define I2C_SDA_1()  IIC_SDA_PORT->BSRR = IIC_SDA_PIN				/* SDA = 1 */
	#define I2C_SDA_0()  IIC_SDA_PORT->BRR = IIC_SDA_PIN				/* SDA = 0 */
	
	#define I2C_SDA_READ()  ((IIC_SDA_PORT->IDR & IIC_SDA_PIN) != 0)	/* ��SDA����״̬ */
#endif


//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);								//����IIC��ʼ�ź�
void IIC_Stop(void);	  						//����IICֹͣ�ź�
void IIC_Ack(void);									//IIC����ACK�ź�
void IIC_NAck(void);								//IIC������ACK�ź�
u8 IIC_Wait_Ack(void); 							//IIC�ȴ�ACK�ź�
void IIC_Send_Byte(u8 txd);					//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�

		 				    
#endif
