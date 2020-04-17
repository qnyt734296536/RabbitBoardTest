#include "Hal_calendar.h"


extern RTC_HandleTypeDef hrtc;


/**
*设置日期
*/
char SetDateAndTime(TRtc_Time time)
{
	RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef DateToUpdate = {0};
  sTime.Hours = time.tm_hour;
  sTime.Minutes = time.tm_min;
  sTime.Seconds = time.tm_sec;

  HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	
  //DateToUpdate.WeekDay = RTC_WEEKDAY_MONDAY;
  DateToUpdate.Month = time.tm_mon;//RTC_MONTH_JANUARY; //必须是BCB码
  DateToUpdate.Date = time.tm_mday;
  DateToUpdate.Year = time.tm_year-1970; //0-99,日期重
	
  HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN);

		return 0;
}

uint8_t GetDateAndTime(TRtc_Time *time)
{
	RTC_TimeTypeDef sTime;
	RTC_DateTypeDef sDate;
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	time->tm_year=sDate.Year+1970;
	time->tm_mon = sDate.Month;
	time->tm_mday=sDate.Date;
	time->tm_wday=sDate.WeekDay;
	time->tm_hour=sTime.Hours;
	time->tm_min=sTime.Minutes;
	time->tm_sec=sTime.Seconds;
	return 0;
}


void TestRtc(void)
{
		//获取RTC
		static int count =0;
		RTC_TimeTypeDef sTime;
	  RTC_DateTypeDef sDate;
		if(count ==0)
		{
			HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
			HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
			LOG("%d:%d:%d:%d-%d:%d:%d\r\n",sDate.Year+1970,sDate.Month,sDate.Date,sDate.WeekDay,sTime.Hours,sTime.Minutes,sTime.Seconds);
		}
		count++;
		if(count > 1000)
		{
			count =0;
		}
}

