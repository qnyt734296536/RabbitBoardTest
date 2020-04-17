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
		GetDateAndTime(&time); //ʱ�Ӿ���
		memset(buf,0,sizeof(buf));
		sprintf(buf,"Time:%d:%d:%d",time.tm_hour,time.tm_min,time.tm_sec);
		OLED_Clear();
		OLED_ShowString(0,0,(uint8_t *)buf,16);
		Delay_Ms(1000);
	}
	for(i=0;i<2;i++)
	{
		dht11ReadData(&temperature, &humidity);//DHT11��ʪ�ȴ�����
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
	
	//û�д�ӡ
	Test_Rgb(); //RGB LED
	Test_Led(); // LED
	Test_Buzzer();//������
	Test_Relay();//�̵���
	Test_Motor();//�ɿ�DC��Դ����
	//Test_Gpio();//��λģ��GPIO
	
	//��Ļ��ʾ
	key = Get_Key_State(); //����
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
	
	state = Get_Pyr_State_Trigger();//���͵�
	if(state==1)
	{
		OLED_Clear();
		OLED_ShowString(0,0,(uint8_t *)"Pyr OK",16);
	}
	
	state = Get_InfTube_State_Trigger();//����Թ�
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
	
	state = Test_Inf_Receiver(); //�������ͷ()
	if(state==1)
	{
		OLED_Clear();
		OLED_ShowString(0,0,(uint8_t *)"InfReciver OK",16);
	}
	
	state = Test_Ligh_Garde_Trigger(); //��������
	if(state==1) 
	{
		OLED_Clear();
		OLED_ShowString(0,0,(uint8_t *)"LightStr OK",16);
	}
	
	//ֱ�Ӵ��ڴ�ӡ
	check_uart_data();	//���Դ���,��չ���� �̶�����10���ֽڣ�Ȼ�󷵻�10���ֽ�
	
		//�д�ӡ
	if(count==0)
	{
		lightAdc = Get_Light_Str_Adc(); //��������
		LOG("lightAdc\t:%1.2f\r\n",lightAdc);
		GetDateAndTime(&time); //ʱ�Ӿ���
		LOG("Time\t:%d-%d-%d<%d>%d:%d:%d\r\n",time.tm_year,time.tm_mon,time.tm_mday,time.tm_wday,time.tm_hour,time.tm_min,time.tm_sec);
		dht11ReadData(&temperature, &humidity);//DHT11��ʪ�ȴ�����
		LOG("DHT11\t:temperature=%d,valueHumidity=%d\r\n",temperature,humidity);
	}
	count++;
	if(count > 3000)
	{
		count = 0;
	}
	
	Delay_Ms(1);
}