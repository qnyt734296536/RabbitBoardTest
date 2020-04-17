#ifndef _HAL_INFRARED_TUBE_H_
#define _HAL_INFRARED_TUBE_H_
#include "common.h"

#define INF_TUBE_PIN	GPIO_PIN_1 //����Թ�PB1
#define INF_TUBE_GPIO_TYPE GPIOB


/**
*���ú�������״̬
*���˸ߵ�ƽ;û�˵͵�ƽ
*/
void Set_InfTube_State(char level);



uint8_t Get_InfTube_State(void);

/**
*�����Թ��Ƿ񱻴���
*/
uint8_t Get_InfTube_State_Trigger(void);


#endif

