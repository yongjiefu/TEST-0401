#include "IIC.h"

/*
*********************************************************************************************************
*	函 数 名: IIC_Init
*	功能说明: 配置I2C总线的GPIO，采用模拟IO的方式实现
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void IIC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(IIC_SCK_CLK, ENABLE);			/* 打开GPIO时钟 */
	GPIO_InitStructure.GPIO_Pin = IIC_SCK_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;	/* 开漏输出 */
	GPIO_Init(IIC_SCK_PORT, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(IIC_SDA_CLK, ENABLE);			/* 打开GPIO时钟 */
	GPIO_InitStructure.GPIO_Pin = IIC_SDA_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;	/* 开漏输出 */
	GPIO_Init(IIC_SCK_PORT, &GPIO_InitStructure);
}


/*
*********************************************************************************************************
*	函 数 名: IIC_Start
*	功能说明: CPU发起I2C总线启动信号
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void IIC_Start(void)
{
	/* SDA设置为输出 */
	IIC_SDA;
	/* 当SCL高电平时，SDA出现一个下跳沿表示I2C总线启动信号 */
	I2C_SDA_1();
	I2C_SCK_1();
	delay_us(4);
	I2C_SDA_0();
	delay_us(4);
	I2C_SCK_0();
	delay_us(4);
}


/*
*********************************************************************************************************
*	函 数 名: IIC_Stop
*	功能说明: CPU发起I2C总线停止信号
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void IIC_Stop(void)
{
	/* SDA设置为输出 */
	IIC_SDA;
	/* 当SCL高电平时，SDA出现一个上跳沿表示I2C总线停止信号 */
	I2C_SDA_0();
	I2C_SCK_1();
	delay_us(4);
	I2C_SDA_1();						   	
}


/*
*********************************************************************************************************
*	函 数 名: IIC_Wait_Ack
*	功能说明: CPU产生一个时钟，并读取器件的ACK应答信号
*	形    参：无
*	返 回 值: 返回0表示正确应答，1表示无器件响应
*********************************************************************************************************
*/
u8 IIC_Wait_Ack(void)
{
	/* SDA设置为输入 */
	READ_SDA;
	I2C_SDA_1();	/* CPU释放SDA总线 */
	delay_us(4);
	I2C_SCK_1();	/* CPU驱动SCL = 1, 此时器件会返回ACK应答 */
	delay_us(4);
	if (I2C_SDA_READ())	/* CPU读取SDA口线状态 */
	{
		I2C_SCK_0();
		delay_us(4);
		return 1;
	}
	else
	{
		I2C_SCK_0();
		delay_us(4);
		return 0;
	}
} 


/*
*********************************************************************************************************
*	函 数 名: IIC_Ack
*	功能说明: CPU产生一个ACK信号
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void IIC_Ack(void)
{
	/* SDA设置为输出 */
	IIC_SDA;
	I2C_SDA_0();	/* CPU驱动SDA = 0 */
	delay_us(4);
	I2C_SCK_1();	/* CPU产生1个时钟 */
	delay_us(4);
	I2C_SCK_0();
	delay_us(4);
	I2C_SDA_1();	/* CPU释放SDA总线 */
}


/*
*********************************************************************************************************
*	函 数 名: IIC_NAck
*	功能说明: CPU产生1个NACK信号
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/	    
void IIC_NAck(void)
{
	/* SDA设置为输出 */
	IIC_SDA;
	I2C_SDA_1();	/* CPU驱动SDA = 1 */
	delay_us(4);
	I2C_SCK_1();	/* CPU产生1个时钟 */
	delay_us(4);
	I2C_SCK_0();
	delay_us(4);	
}					 				     


/*
*********************************************************************************************************
*	函 数 名: IIC_Send_Byte
*	功能说明: CPU向I2C总线设备发送8bit数据
*	形    参：txd ： 等待发送的字节
*	返 回 值: 无
*********************************************************************************************************
*/
void IIC_Send_Byte(u8 txd)
{
  u8 i;
	/* SDA设置为输出 */
	IIC_SDA;
	IIC_SCL=0;//拉低时钟开始数据传输
	for(i=0;i<8;i++)
	{              
		IIC_SDA=(txd&0x80)>>7;
		txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
	}
}


/*
*********************************************************************************************************
*	函 数 名: i2c_ReadByte
*	功能说明: CPU从I2C总线设备读取8bit数据
*	形    参：ack ： ack=1时，发送ACK，ack=0，发送nACK
*	返 回 值: 读到的数据
*********************************************************************************************************
*/
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	/* SDA设置为输入 */
	READ_SDA;
  for(i=0;i<8;i++ )
	{
		IIC_SCL=0; 
		delay_us(2);
		IIC_SCL=1;
		receive<<=1;
		if(READ_SDA)
			receive++;   
		delay_us(1); 
  }
	if (!ack)
		IIC_NAck();//发送nACK
	else
		IIC_Ack(); //发送ACK   
	return receive;
}
