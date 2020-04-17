#ifndef _HAL_KEY_H_
#define _HAL_KEY_H_

#include "common.h"

#define KEY1_PIN  GPIO_PIN_15 //PA15
#define KEY2_PIN  GPIO_PIN_10 //PC10
#define KEY3_PIN  GPIO_PIN_11 //PC11

#define KEY1_GPIO_TYPE GPIOA
#define KEY2_GPIO_TYPE GPIOC
#define KEY3_GPIO_TYPE GPIOC

/*
*���ð���״̬
*����а��£������ö��ڰ�������
*key��Χ1-3

*/
uint8_t Set_Key_State(uint8_t key);


/**
*���ذ����İ���,���غ�Ѱ������
*����ֵ1-3
*/
uint8_t Get_Key_State(void);
#endif

