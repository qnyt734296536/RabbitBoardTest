#include "Hal_pyr.h"

static uint8_t  gPyrState = 0;
static uint8_t  gTrigger = 0;

/**
*��ʱ�ĵ�ƽ
*���˸ߵ�ƽ;û�˵͵�ƽ
*/
void Set_Pyr_State(char level)
{
	gPyrState = level;
	if(gPyrState == 1)
	{
		gTrigger =1;
	}
	//LOG("Set Pyr levle is %d, PyrState is %d\r\n",level,gPyrState);
}


/**
*��ȡ���͵��Ƿ񱻴���
*/
uint8_t Get_Pyr_State_Trigger(void)
{
	uint8_t state = 0;
	
	if(gTrigger == 1)
	{
		gTrigger = 0;
		state = 1;
	}
	return state;
}


