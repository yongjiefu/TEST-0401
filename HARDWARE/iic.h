#ifndef __IIC_H
#define __IIC_H	 

#include "sys.h"
#include "delay.h"


#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据


/* 定义I2C总线连接的GPIO端口, 用户只需要修改下面4行代码即可任意改变SCL和SDA的引脚 */

#define	IIC_SCK_PIN		GPIO_Pin_6						/* 连接到SCK时钟线的GPIO */
#define IIC_SCK_PORT	GPIOB									/* GPIO端口 */
#define IIC_SCK_CLK		RCC_APB2Periph_GPIOB	/* GPIO端口时钟 */
#define IIC_SCL    		PBout(6)							//SCL

#define	IIC_SDA_PIN		GPIO_Pin_7						/* 连接到SDA时钟线的GPIO */
#define IIC_SDA_PORT	GPIOB									/* GPIO端口 */
#define IIC_SDA_CLK		RCC_APB2Periph_GPIOB	/* GPIO端口时钟 */
#define IIC_SDA    		PBout(7)							//SDA
#define READ_SDA   		PBin(7)								//输入SDA


/* 定义读写SCL和SDA的宏，已增加代码的可移植性和可阅读性 */
#if 0		/* 条件编译： 1 选择GPIO的库函数实现IO读写 */
	#define I2C_SCK_1()  GPIO_SetBits(IIC_SCK_PORT,IIC_SCK_PIN)			/* SCL = 1 */
	#define I2C_SCK_0()  GPIO_ResetBits(IIC_SCK_PORT,IIC_SCK_PIN)		/* SCL = 0 */
	
	#define I2C_SDA_1()  GPIO_SetBits(IIC_SDA_PORT,IIC_SDA_PIN)			/* SDA = 1 */
	#define I2C_SDA_0()  GPIO_ResetBits(IIC_SDA_PORT,IIC_SDA_PIN)		/* SDA = 0 */
	
	#define I2C_SDA_READ()  GPIO_ReadInputDataBit(GPIO_PORT_I2C,I2C_SDA_PIN)	/* 读SDA口线状态 */
#else	/* 这个分支选择直接寄存器操作实现IO读写 */
	/*　注意：如下写法，在IAR最高级别优化时，会被编译器错误优化 */
	#define I2C_SCK_1()  IIC_SCK_PORT->BSRR = IIC_SCK_PIN				/* SCL = 1 */
	#define I2C_SCK_0()  IIC_SCK_PORT->BRR = IIC_SCK_PIN				/* SCL = 0 */
	
	#define I2C_SDA_1()  IIC_SDA_PORT->BSRR = IIC_SDA_PIN				/* SDA = 1 */
	#define I2C_SDA_0()  IIC_SDA_PORT->BRR = IIC_SDA_PIN				/* SDA = 0 */
	
	#define I2C_SDA_READ()  ((IIC_SDA_PORT->IDR & IIC_SDA_PIN) != 0)	/* 读SDA口线状态 */
#endif


//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);								//发送IIC开始信号
void IIC_Stop(void);	  						//发送IIC停止信号
void IIC_Ack(void);									//IIC发送ACK信号
void IIC_NAck(void);								//IIC不发送ACK信号
u8 IIC_Wait_Ack(void); 							//IIC等待ACK信号
void IIC_Send_Byte(u8 txd);					//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节

		 				    
#endif
