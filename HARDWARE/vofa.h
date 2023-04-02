#ifndef __VOFA_H
#define __VOFA_H

#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "stdio.h"
#include "delay.h"
#include "string.h"

void vofa_send(float channel_1,float channel_2,float channel_3,float channel_4);

#endif


