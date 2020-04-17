#ifndef _HAL_GPIO_H_
#define _HAL_GPIO_H_

#include "common.h"



//2G 4G 核心板为高电平复位
//WIFI 核心板为低电平复位
void Set_Module_Reset(void);

void Test_Gpio(void);

#endif

