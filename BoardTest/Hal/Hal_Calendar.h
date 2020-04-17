#ifndef _HAL_CALENDAR_H_
#define _HAL_CALENDAR_H_

#include "common.h"

/**
*10进制的时间结构体
*/
typedef struct
{
	char tm_sec;
	char tm_min;
	char tm_hour;
	char tm_mday;
	char tm_mon;
	int  tm_year;
	char tm_wday;
}TRtc_Time; 

uint8_t GetDateAndTime(TRtc_Time *time);

void TestRtc(void);

#endif


