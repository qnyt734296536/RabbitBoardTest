#ifndef _HAL_PYR_H_
#define _HAL_PYR_H_

#include "common.h"

#define PYR_PIN	GPIO_PIN_4 //���͵�PC4
#define PYR_GPIO_TYPE GPIOC


/**
*��ʱ�ĵ�ƽ
*���˸ߵ�ƽ;û�˵͵�ƽ
*/
void Set_Pyr_State(char level);


/**
*��ȡ���͵��Ƿ񱻴���
*/
uint8_t  Get_Pyr_State(void);


/**
*��ȡ���͵��Ƿ񱻴���
*/
uint8_t Get_Pyr_State_Trigger(void);

#endif

