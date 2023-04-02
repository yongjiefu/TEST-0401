#include "vofa.h"

static unsigned char tempData[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0x80,0x7f};

void vofa_send(float channel_1,float channel_2,float channel_3,float channel_4)
{
    unsigned int i;
    static float temp[4];
    
    temp[0] = channel_1;
    temp[1] = channel_2;
    temp[2] = channel_3;
    temp[3] = channel_4;
  
    memcpy(tempData,(unsigned char *)temp,sizeof(temp));    
    for(i = 0;i<20;i++){
        USART_SendData(USART1,tempData[i]);
        delay_us(100);
    }
}



