#include "Hal_Infrared_Tube.h"

static uint8_t gInfTubeState = 0;
static uint8_t  gTrigger = 0;

/**
*���ú�������״̬
*�͵�ƽ�ڵ����ߵ�ƽû�ڵ�
*/
void Set_InfTube_State(char level)
{
	gInfTubeState = level;
	if(gInfTubeState == 0)
	{
		gTrigger = 1;
	}
	LOG("Set infTube levle is %d, gInfState is %d\r\n",level,gInfTubeState);
}



uint8_t Get_InfTube_State(void)
{
	return gInfTubeState;
}



/**
*�����Թ��Ƿ񱻴���
*/
uint8_t Get_InfTube_State_Trigger(void)
{
	uint8_t state = 0;
	
	if(gTrigger == 1)
	{
		gTrigger = 0;
		state = 1;
	}
	return state;
}


