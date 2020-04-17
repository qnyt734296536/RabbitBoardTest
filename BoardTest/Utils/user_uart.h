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
*����һ���жϽ���
*/
void init_uart_uart(void);

/**
*��⴮��1������
* ��Ҫ�и��жϱ�׼�������ж�Э���Ƿ����
* ˫��Ҳ��Ҫ��һ�����ӳ�
*/
void check_uart_data(void);


void Init_Rs485(void);
uint8_t Check_Rs485_data(void);

#endif


