#ifndef _HAL_LED_H_
#define _HAL_LED_H_

#include "common.h"

//����LED���
#define LED1 1
#define LED2 2
#define LED3 3
#define LED4 4


/**
*���ƿ������ϵ�4��LED
*/
void Control_Led(char led,char state);


/**
*���� LED
*/
void Test_Led(void);

#endif

