#include "board_test.h"
#include "delay.h"
#include "Hal_Led.h"
#include "Hal_key.h"
#include "user_uart.h"
#include "Hal_Buzzer.h"
#include "Hal_Relay.h"
#include "Hal_Light_Resistor.h"
#include "Hal_Motor.h"
#include "Hal_Calendar.h"
#include "Hal_Rgb_My9291.h"
#include "Hal_Inf_Receiver.h"
#include "Hal_Oled.h"
#include "Hal_Temp_Hum.h"
#include "Hal_Gpio.h"
#include "Hal_pyr.h"
#include "Hal_Infrared_tube.h"



void BaordInit(void)
{
	TRtc_Time time;
	uint8_t temperature =0,humidity = 0;
	char buf[50];
	int i =0;
	LOG("Hello Rabbit!\r\n");
	Delay_Init(72);
	init_uart_uart();
	Init_Buzzer();
	Init_Relay();
	Init_Motor();
	Init_My9291();
	OLED_Init();
	Init_Rs485();
	OLED_Show_Bmp_Test();
	Delay_Ms(1000);
	
	for(i=0;i<2;i++)
	{
		GetDateAndTime(&time); //时钟晶振
		memset(buf,0,sizeof(buf));
		sprintf(buf,"Time:%d:%d:%d",time.tm_hour,time.tm_min,time.tm_sec);
		OLED_Clear();
		OLED_ShowString(0,0,(uint8_t *)buf,16);
		Delay_Ms(1000);
	}
	for(i=0;i<2;i++)
	{
		dht11ReadData(&temperature, &humidity);//DHT11温湿度传感器
		memset(buf,0,sizeof(buf));
		sprintf(buf,"DHT11:T=%d,H=%d",temperature,humidity);
		OLED_Clear();
		OLED_ShowString(0,0,(uint8_t *)buf,16);
		Delay_Ms(1000);
		Delay_Ms(1000);
	}

}


void BoardTest(void)
{
	static uint32_t count =0;
	TRtc_Time time;
	uint8_t temperature =0,humidity = 0;
	float lightAdc=0;
	uint8_t key=0;
	uint8_t state = 0;
	
	//没有打印
	Test_Rgb(); //RGB LED
	Test_Led(); // LED
	Test_Buzzer();//蜂鸣器
	Test_Relay();//继电器
	Test_Motor();//可控DC电源开关
	//Test_Gpio();//复位模组GPIO
	
	//屏幕显示
	key = Get_Key_State(); //按键
	if(key==1)
	{
		OLED_Clear();
		OLED_ShowString(0,0,(uint8_t *)"Key1",16);
	}
	else if(key==2)
	{
		OLED_Clear();
		OLED_ShowString(0,0,(uint8_t *)"Key2",16);
	}
	else if(key==3)
	{
		OLED_Clear();
		OLED_ShowString(0,0,(uint8_t *)"Key3",16);
	}
	
	state = Get_Pyr_State_Trigger();//热释电
	if(state==1)
	{
		OLED_Clear();
		OLED_ShowString(0,0,(uint8_t *)"Pyr OK",16);
	}
	
	state = Get_InfTube_State_Trigger();//红外对管
	if(state==1)
	{
		OLED_Clear();
		OLED_ShowString(0,0,(uint8_t *)"InfTube OK",16);
	}
	
	state = Check_Rs485_data();//RS485
	if(state==1)
	{
		OLED_Clear();
		OLED_ShowString(0,0,(uint8_t *)"RS485 OK",16);
	}
	
	state = Test_Inf_Receiver(); //红外接收头()
	if(state==1)
	{
		OLED_Clear();
		OLED_ShowString(0,0,(uint8_t *)"InfReciver OK",16);
	}
	
	state = Test_Ligh_Garde_Trigger(); //光敏电阻
	if(state==1) 
	{
		OLED_Clear();
		OLED_ShowString(0,0,(uint8_t *)"LightStr OK",16);
	}
	
	//直接串口打印
	check_uart_data();	//调试串口,扩展串口 固定接收10个字节，然后返回10个字节
	
		//有打印
	if(count==0)
	{
		lightAdc = Get_Light_Str_Adc(); //光敏电阻
		LOG("lightAdc\t:%1.2f\r\n",lightAdc);
		GetDateAndTime(&time); //时钟晶振
		LOG("Time\t:%d-%d-%d<%d>%d:%d:%d\r\n",time.tm_year,time.tm_mon,time.tm_mday,time.tm_wday,time.tm_hour,time.tm_min,time.tm_sec);
		dht11ReadData(&temperature, &humidity);//DHT11温湿度传感器
		LOG("DHT11\t:temperature=%d,valueHumidity=%d\r\n",temperature,humidity);
	}
	count++;
	if(count > 3000)
	{
		count = 0;
	}
	
	Delay_Ms(1);
}