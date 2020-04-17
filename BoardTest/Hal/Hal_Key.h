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
*设置按键状态
*如果有按下，就设置对于按键触发
*key范围1-3

*/
uint8_t Set_Key_State(uint8_t key);


/**
*返回按过的按键,返回后把按键清空
*返回值1-3
*/
uint8_t Get_Key_State(void);
#endif

