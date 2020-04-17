#include "Hal_Motor.h"

#define MOTOR_PIN	GPIO_PIN_6 //12VÊä³ö PC6
#define MOTOR_GPIO_TYPE GPIOC

void Init_Motor(void)
{
	HAL_GPIO_WritePin(MOTOR_GPIO_TYPE,MOTOR_PIN,GPIO_PIN_RESET);
}



void Set_Motor_State(char on_off)
{
	if (on_off == 1)
	{
	
		HAL_GPIO_WritePin(MOTOR_GPIO_TYPE,MOTOR_PIN,GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(MOTOR_GPIO_TYPE,MOTOR_PIN,GPIO_PIN_RESET);
	}

}



void Test_Motor(void)
{
	static uint16_t count=0;
	if(count ==0)
	{
		Set_Motor_State(1);
	}
	else if(count ==1000)
	{
		Set_Motor_State(0);
	}
	else if(count >1500)
  {
		count =0;
	}
	
	count++;

}
