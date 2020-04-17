#ifndef _USER_UART_H_
#define _USER_UART_H_

#define UART1_RECEIVE_CACHE_LEN 100 
#define UART2_RECEIVE_CACHE_LEN 100
#define UART3_RECEIVE_CACHE_LEN 100

#include "common.h"

typedef enum 
{
	RS485_STATE_R,
	RS485_STATE_W
}Rs485State;

/**
*开启一次中断接收
*/
void init_uart_uart(void);

/**
*检测串口1的数据
* 需要有个判断标准，用来判断协议是否完成
* 双方也需要有一定的延迟
*/
void check_uart_data(void);


void Init_Rs485(void);
uint8_t Check_Rs485_data(void);

#endif


