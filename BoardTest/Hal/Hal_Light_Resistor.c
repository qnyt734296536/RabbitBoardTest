#include "Hal_Light_Resistor.h"



//�������� ,ʹ�� PC0 ADC1 ͨ��10 �ж� �ɼ�
extern ADC_HandleTypeDef hadc1;





/**
*ADC �жϺ���
*/
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	LOG("adc\r\n");

}



float Get_Light_Str_Adc(void)
{
	uint16_t value =0;
	float adc = 0.0;
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 10);    //�ȴ�ת����ɣ��ڶ���������ʾ��ʱʱ�䣬��λms        
	if(HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC))
	{
			value=HAL_ADC_GetValue(&hadc1);
	}
	adc = (float)value*3.3/4096;
	return adc;
}
/**
*��ȡ����ǿ�ȵȼ�
*/
uint8_t Get_Light_Str_Garde(void)
{
	uint16_t value =0;
	uint8_t grade = 1;
	float adc = 0.0;
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 10);    //�ȴ�ת����ɣ��ڶ���������ʾ��ʱʱ�䣬��λms        
	if(HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC))
	{
			value=HAL_ADC_GetValue(&hadc1);
	}
	adc = (float)value*3.3/4096;
	LOG("PC0 ADC : %.4f \r\n",adc); 
	if(adc > 2.5)
	{
		grade = 0; //��ҹ
	}
	return grade;
}


void Test_Ligh_Garde(void)
{
	static uint16_t count=0;
	if(count ==1)
	{
		Get_Light_Str_Garde();
	}
	if(count >1000)
	{
		count =0;
	}
	count++;
}

/**�����Ƿ񱻴���*/
uint8_t Test_Ligh_Garde_Trigger(void)
{
		float adc =0.0;
		float ext =2.5;
		static uint8_t st1=0,st2=0;
		uint8_t  gTrigger = 0;
	  
		adc= Get_Light_Str_Adc();
		if(adc <ext)
		{
			st1=1;
		}
		else
		{
			st2 =1;
		}

		if(st1 == 1 && st2==1)
		{
			gTrigger =1;
			st1=0;
			st2=0;
		}
		
		return gTrigger;
}

