#include "Hal_Key.h"

uint8_t gKeyState[3]={0};

/*
*设置按键状态
*如果有按下，就设置对于按键触发
*key范围1-3

*/
uint8_t Set_Key_State(uint8_t key)
{
	if(key<1 || key>3)
	{
		return 1;
	}
	gKeyState[key-1]=1;
	LOG("key=%d,state=%d\r\n",key,gKeyState[key-1]);
	return 0;
}

/**
*返回按过的按键,返回后把按键清空
*返回值1-3
*/
uint8_t Get_Key_State(void)
{
	char i =0;
	uint8_t key = 0;
	for(i=0;i<3;i++)
	{
		if(gKeyState[i] == 1)
		{
			key =i+1;
			gKeyState[i]=0;
			LOG("key=%d\r\n",key);
		}
	}

	
	return key;
}




