#include "Hal_Gpio.h"

//���ڸ�λģ��Ĺܽ�
#define RESET_MOULE_PIN GPIO_PIN_3
#define RESET_MOULE_PROT GPIOC


//2G 4G ���İ�Ϊ�ߵ�ƽ��λ
//WIFI ���İ�Ϊ�͵�ƽ��λ
void Init_Gpio(void)
{
	HAL_GPIO_WritePin(RESET_MOULE_PROT, RESET_MOULE_PIN, GPIO_PIN_SET);//
}

//2G 4G ���İ�Ϊ�ߵ�ƽ��λ
//WIFI ���İ�Ϊ�͵�ƽ��λ
void Set_Module_Reset(void)
{
	HAL_GPIO_WritePin(RESET_MOULE_PROT, RESET_MOULE_PIN, GPIO_PIN_SET);//
	Delay_Ms(20);
	
	HAL_GPIO_WritePin(RESET_MOULE_PROT, RESET_MOULE_PIN, GPIO_PIN_RESET);//
}

void Test_Gpio(void)
{
	static int count =0;
	if(count == 1)
	{
		HAL_GPIO_WritePin(RESET_MOULE_PROT, RESET_MOULE_PIN, GPIO_PIN_SET);//
	}
	else if(count == 1000)
	{
		HAL_GPIO_WritePin(RESET_MOULE_PROT, RESET_MOULE_PIN, GPIO_PIN_RESET);
	}
	if(count > 1500)
	{
		count=0;
	}
		
	count ++;
}
