#ifndef _HAL_INF_RECEIVER_H_
#define _HAL_INF_RECEIVER_H_


#include "common.h"


#define INF_RECEIVER_PIN GPIO_PIN_2
#define INF_RECEIVER_GPIO_TYPE GPIOD


void Pro_Inf_Receiver_Pin_Eint(char level);

uint8_t Test_Inf_Receiver(void);

/**≤‚ ‘ «∑Ò±ª¥•∑¢*/
uint8_t Test_Ligh_Garde_Trigger(void);

#endif

