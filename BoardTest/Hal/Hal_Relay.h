#ifndef _HAL_RELAY_H_
#define _HAL_RELAY_H_

#include "common.h"

#define RELAY_STATE_OFF 0   //�̵����ر�
#define RELAY_STATE_ON 1    //�̵�����

/**
*��ʼ���̵���
*/
void Init_Relay(void);

/**
*���Ƽ̵�������
*�ߵ�ƽOut2,�͵�ƽout1
*/
void Control_Relay(char state);



void Test_Relay(void);
#endif

