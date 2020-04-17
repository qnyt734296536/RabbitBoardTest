#include "user_pro_eint.h"
#include "Hal_Key.h"
#include "Hal_Pyr.h"
#include "Hal_Infrared_Tube.h"
#include "Hal_Inf_Receiver.h"


/**
*GPIO 外部中断的回调函数
*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	char state = 0;

	if(GPIO_Pin == INF_RECEIVER_PIN) //红外遥控接受头
	{
		state = HAL_GPIO_ReadPin(INF_RECEIVER_GPIO_TYPE, INF_RECEIVER_PIN);
		Pro_Inf_Receiver_Pin_Eint(state);
		
	}
	else if(GPIO_Pin == KEY1_PIN) //按键
	{
		state = HAL_GPIO_ReadPin(KEY1_GPIO_TYPE, KEY1_PIN);
		//LOG("key1 state is %d\r\n",state);
		if(state == 0)
		{
			Set_Key_State(1);
		}
	}
	else if (GPIO_Pin == KEY2_PIN)
	{
		state = HAL_GPIO_ReadPin(KEY2_GPIO_TYPE, KEY2_PIN);
		//LOG("key2 state is %d\r\n",state);
		if(state == 0)
		{
			Set_Key_State(2);
		}
	}
	else if(GPIO_Pin == KEY3_PIN)
	{
		state = HAL_GPIO_ReadPin(KEY3_GPIO_TYPE, KEY3_PIN);
		//LOG("key3 state is %d\r\n",state);
		if(state == 0)
		{
			Set_Key_State(3);
		}
	}
	else if (GPIO_Pin == PYR_PIN)//热释电
	{
		state = HAL_GPIO_ReadPin(PYR_GPIO_TYPE, PYR_PIN);

		Set_Pyr_State(state);
		
		//LOG("pyr state is %d\r\n",state);
	}
	
	else if (GPIO_Pin == INF_TUBE_PIN)//红外对管
	{
		state = HAL_GPIO_ReadPin(INF_TUBE_GPIO_TYPE, INF_TUBE_PIN);

		Set_InfTube_State(state);
		
		//LOG("inf tube state is %d\r\n",state);
	}

	

}

