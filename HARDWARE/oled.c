#include "oled.h"
#include "oledfont.h"


//OLED���Դ�
//��Ÿ�ʽ����.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 			   

/*
 �Զ���OLED ����ϵ����: ������OLED ֱ������ϵ�� x,y�ᷴ�� ���㺯�����㡿
			��y
		    |
	        127----------
			|	     |
			|		 |
			|		 |
			|		 |
			|		 |
			|		 |
		  (0,0)----------��x  
						63
*/


u8 OLED_GRAM[128][8];	


//�����Դ浽LCD
void OLED_Refresh_Gram(void)
{
	u8 i,n;
	for(i=0;i<8;i++)
	{
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ
		for(n=0;n<128;n++)
		{
			OLED_WR_Byte(OLED_GRAM[n][i],OLED_DATA);
		}
	}
}


/**********************************************
// IIC Write Command
**********************************************/
void OLED_Write_Command(unsigned char IIC_Command)
{
  IIC_Start();
  IIC_Send_Byte(OLED_Address);					//OLED�豸��ַ
	IIC_Wait_Ack();
  IIC_Send_Byte(OLED_Cmd_Address);			//д�����ַ
	IIC_Wait_Ack();
  IIC_Send_Byte(IIC_Command);						//д������
	IIC_Wait_Ack();
  IIC_Stop();
}


/**********************************************
// IIC Write Data
**********************************************/
void OLED_Write_Data(unsigned char IIC_Data)
{
  IIC_Start();
  IIC_Send_Byte(OLED_Address);					//OLED�豸��ַ
	IIC_Wait_Ack();
  IIC_Send_Byte(OLED_Data_Address);			//д���ݵ�ַ
	IIC_Wait_Ack();	
  IIC_Send_Byte(IIC_Data);							//д������
	IIC_Wait_Ack();
  IIC_Stop();
}


void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
	if(cmd)
	{
		OLED_Write_Data(dat);
	}
	else
	{
   OLED_Write_Command(dat);
	}
}


/********************************************
// fill_Picture
********************************************/
void fill_picture(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		OLED_WR_Byte(0xb0+m,0);			//page0-page1
		OLED_WR_Byte(0x00,0);				//low column start address
		OLED_WR_Byte(0x10,0);				//high column start address
		for(n=0;n<128;n++)
		{
			OLED_WR_Byte(fill_Data,1);
		}
	}
}


//��������
void OLED_Set_Pos(unsigned char x, unsigned char y)
{
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD);
}


//����OLED��ʾ
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}


//�ر�OLED��ʾ
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}


//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��!!!
void OLED_Clear(void)
{
	u8 i,n;
	for(n=0;n<8;n++)
	{
		for(i=0;i<128;i++)
		{
			OLED_GRAM[i][n]=0;
		}
	}
	OLED_Refresh_Gram();
	for(i=0;i<8;i++)
	{
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ
		for(n=0;n<128;n++)
		{
			OLED_WR_Byte(0,OLED_DATA);
		}
	}	//������ʾ
}


//����
//x:0~127
//y:0~63
//t:1 ��� 0,���
void OLED_DrawPoint(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;
	if(x>127||y>63)
	{
		return;//������Χ��
	}
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)
	{
		OLED_GRAM[x][pos]|=temp;
	}
	else 
	{
		OLED_GRAM[x][pos]&=~temp;
	}
	OLED_Refresh_Gram();
}


//x1,y1,x2,y2 �������ĶԽ�����
//ȷ��x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63
//dot:0,���;1,���
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot)
{
	u8 x,y;
	for(x=x1;x<=x2;x++)
	{
		for(y=y1;y<=y2;y++)
		{
			OLED_DrawPoint(x,y,dot);
		}
	}
	OLED_Refresh_Gram();//������ʾ
}


void OLED_On(void)
{
	u8 i,n;
	for(i=0;i<8;i++)
	{
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ
		for(n=0;n<128;n++)
		{
			OLED_WR_Byte(1,OLED_DATA);
		}
	}	//������ʾ
}


//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//mode:0,������ʾ;1,������ʾ
//size:ѡ������ 16/12
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size)
{
	unsigned char c=0,i=0;
	c=chr-' ';//�õ�ƫ�ƺ��ֵ
	if(x>Max_Column-1)
	{
		x=0;
		y=y+2;
	}
	if(Char_Size ==16)
	{
		OLED_Set_Pos(x,y);
		for(i=0;i<8;i++)
		{
			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
		}
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++)
		{
			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
		}
	}
	else
	{
		OLED_Set_Pos(x,y);
		for(i=0;i<6;i++)
		{
			OLED_WR_Byte(F6x8[c][i],OLED_DATA);
		}
	}
}


//m^n����
u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;
	while(n--)
	{
		result*=m;
	}
	return result;
}


//��ʾ2������
//x,y :�������
//len :���ֵ�λ��
//size:�����С
//mode:ģʽ	0,���ģʽ;1,����ģʽ
//num:��ֵ(0~4294967295);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2)
{
	u8 t,temp;
	u8 enshow=0;
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}
			else
			{
				enshow=1;
			}
		}
	 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2);
	}
}


//��ʾһ���ַ��Ŵ�
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{
		OLED_ShowChar(x,y,chr[j],Char_Size);
		x+=8;
		if(x>120)
		{
			x=0;
			y+=2;
		}
		j++;
	}
}


//��ʾ����
void OLED_ShowCHinese(u8 x,u8 y,u8 no)
{
	u8 t,adder=0;
	OLED_Set_Pos(x,y);
	for(t=0;t<16;t++)
	{
		OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
		adder+=1;
	}
	OLED_Set_Pos(x,y+1);
	for(t=0;t<16;t++)
	{
		OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
		adder+=1;
	}
}


/***********������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{
	unsigned int j=0;
	unsigned char x,y;
	
  if(y1%8==0)
	{
		y=y1/8;
	}
  else
	{
		y=y1/8+1;
	}
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
		{
			OLED_WR_Byte(BMP[j++],OLED_DATA);
		}
	}
}


//��ʼ��OLED
void OLED_Init(void)
{   
    IIC_Init();
	IIC_Stop();
	delay_ms(800);
	OLED_WR_Byte(0xAE,OLED_CMD);//--display off
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address
	OLED_WR_Byte(0xB0,OLED_CMD);//--set page address
	OLED_WR_Byte(0x81,OLED_CMD); // contract control
	OLED_WR_Byte(0xFF,OLED_CMD);//--128
	OLED_WR_Byte(0xA1,OLED_CMD);//set segment remap
	OLED_WR_Byte(0xA6,OLED_CMD);//--normal / reverse
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3F,OLED_CMD);//--1/32 duty
	OLED_WR_Byte(0xC8,OLED_CMD);//Com scan direction
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset
	OLED_WR_Byte(0x00,OLED_CMD);//
	
	OLED_WR_Byte(0xD5,OLED_CMD);//set osc division
	OLED_WR_Byte(0x80,OLED_CMD);//
	
	OLED_WR_Byte(0xD8,OLED_CMD);//set area color mode off
	OLED_WR_Byte(0x05,OLED_CMD);//
	
	OLED_WR_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
	OLED_WR_Byte(0xF1,OLED_CMD);//
	
	OLED_WR_Byte(0xDA,OLED_CMD);//set com pin configuartion
	OLED_WR_Byte(0x12,OLED_CMD);//
	
	OLED_WR_Byte(0xDB,OLED_CMD);//set Vcomh
	OLED_WR_Byte(0x30,OLED_CMD);//
	
	OLED_WR_Byte(0x8D,OLED_CMD);//set charge pump enable
	OLED_WR_Byte(0x14,OLED_CMD);//
	
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
    OLED_Clear();
}


/* �������� */
void Boot_Animation(void)
{
	static u8 x=0,y=0;
	for(x = 63;x>=18;x--)
	{
		OLED_DrawPoint(108-0.7*x,x,1);	//��б�� б�ʡ֡�3/3
		OLED_DrawPoint(17 +0.7*x,x,1);
		y = 64-x;
		OLED_DrawPoint(64-0.7*y,y,1);
		OLED_DrawPoint(64+0.7*y,y,1);
		OLED_Refresh_Gram();						//������ʾ��OLED
	}
	for(x = 30;x <= 94;x++)
	{
		OLED_DrawPoint(125-x,47,1);
		OLED_DrawPoint(x,18,1);
		OLED_Refresh_Gram();						//������ʾ��OLED
	}
}


/*
���ߺ���
��ڲ�����
x1������x���ꣻ
y1������y���ꣻ
x2���յ��x���ꣻ
y2���յ��y���ꣻ
*/
void OLED_DrawLine(unsigned int x1, unsigned int y1, unsigned int x2,unsigned int y2)
{
	unsigned int t;
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	delta_x=x2-x1;	//������������
	delta_y=y2-y1;
	uRow=x1;
	uCol=y1;
	if(delta_x>0)incx=1;	//���õ�������
	else if(delta_x==0)incx=0;//��ֱ��
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if(delta_y==0)incy=0;//ˮƽ��
	else{incy=-1;delta_y=-delta_y;}
	if( delta_x>delta_y)distance=delta_x; //ѡȡ��������������
	else distance=delta_y;
	for(t=0;t<=distance+1;t++ )//�������
	{
		OLED_DrawPoint(uRow,uCol,1);//����
		xerr+=delta_x;
		yerr+=delta_y;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}


