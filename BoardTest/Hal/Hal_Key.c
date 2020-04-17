#include "Hal_Key.h"

uint8_t gKeyState[3]={0};

/*
*���ð���״̬
*����а��£������ö��ڰ�������
*key��Χ1-3

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
*���ذ����İ���,���غ�Ѱ������
*����ֵ1-3
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




