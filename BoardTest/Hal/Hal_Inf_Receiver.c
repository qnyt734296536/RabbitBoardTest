#include "Hal_Inf_Receiver.h"

/**
*�������ʹ��PD2,ֻ��ʹ��IO�ж�, �붨ʱ�����,����ʹ�õ�TIM3��ʱ��,��ʱ56usһ���ж�
*���� NECЭ��ĺ������,�ֱ�Ϊ ͬ���� ��ַ�� ��ַ���� ������ ���Ʒ��� ����������
*�ܽ�Ĭ��Ϊ�ߵ�ƽ
*���9ms�͵�ƽ��4.5ms�ߵ�ƽΪ��ʼ�ź�
*���560us �͵�ƽ��560us�ߵ�ƽ Ϊ�߼�0
*���560us �͵�ƽ��1680us�ߵ�ƽΪ�߼�1
*���9ms�͵�ƽ2.5ms�ߵ�ƽ(������������),0.56ms�͵�ƽ,����110ms  Ϊ������
*����20msû��⵽��ƽ�仯,��ʾһ�����ݷ������(��������������)
*�������ǰ����ݽ�����ɺ�(����34���½����жϺ�),���������
*����bitΪ�ӵ���Чλ��ʼ��
*/


extern TIM_HandleTypeDef htim3;

typedef struct
{
	char syn_flag; //�Ƿ���ܵ�ͬ����
	char time_start_flag; //��ʱ���������
	
	uint32_t all_time; //��ʱʱ�䵥λ��ʱ�����ʱ��
	uint32_t last_data_time;//��һ�����ݵ�ʱ��, ��һ�μ�ȥ��һ�ε�ʱ�䣬�ͱ�ʾ��һ���жϵ�����жϵ�ʱ��
	uint16_t eint_count ; //�жϴ���
	uint16_t differ_time[40];//��¼�����ж�����һ���ж�����ʱ��
}TInf_Recive_State;

#define TIME_UNIT 56  //��ʱ����λus
#define ERROR_TIME (TIME_UNIT*2) //��Χ
#define DATA_SYN 13500//ͬ���� �жϼ��ʱ��(9000+4500)
#define DATA_L 1120  //����0 ���жϼ��ʱ��,(560+560)
#define DATA_H 2240  //����1 ���жϼ��ʱ��,560+1680
#define MAX_WAIT_TIME 100000  //��ȴ�100ms,�����յ���ͬ�����,����������ʱ��û���ж���,��ʾ����ȫ������(����������)

TInf_Recive_State gInf_State;
TIM_HandleTypeDef *ginf_htim = &htim3;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

	if(htim == ginf_htim)
	{
		gInf_State.all_time+=TIME_UNIT; 
	}

}
/**
*��������жϹܽŵĵ�ƽ
*/
void Pro_Inf_Receiver_Pin_Eint(char level)
{
	//1.��һ���жϺ�,������ʱ��
	uint32_t differ_time = 0; 
	if (gInf_State.time_start_flag == 0)
	{
		memset(&gInf_State,0,sizeof(gInf_State));
		HAL_TIM_Base_Start_IT(ginf_htim); //��һ�ν����жϵ�ʱ�򡣿�����ʱ����ʱ��Ƚ���,���µ�һ�����ʱ�䲻׼ȷ�������ᵽ�ⲿ�ж����ﴦ��
		gInf_State.time_start_flag = 1;
	}
	else
	{
		//2.�������ʱ��
		differ_time = gInf_State.all_time-gInf_State.last_data_time;
		
		//3.Ѱ��ͬ����
		if(gInf_State.syn_flag == 0 && gInf_State.eint_count == 0) //���û���յ�ͬ����,��Ҫ�ȴ�ͬ����
		{
			if((DATA_SYN-5*ERROR_TIME)<differ_time && differ_time < (DATA_SYN+ERROR_TIME))////��һ�ν����жϵ�ʱ���ʱ���е������µ�һ���������Ƚϴ�
			{
				gInf_State.syn_flag = 1;
			}
		}

		gInf_State.differ_time[gInf_State.eint_count++]=differ_time;//������жϸ���,û�취�������ӳټ�¼������
		gInf_State.last_data_time = gInf_State.all_time;
 }

}


/**
*��ȡ�������ͷ����
*������,����1,������Ч
*/
uint8_t Check_Inf_Reciver_Data(uint8_t *addr,uint8_t * cmd)
{
	uint8_t ret = 0;
	char j=0,k=0;
	uint8_t inf_data[4]={0};
	if((gInf_State.all_time-gInf_State.last_data_time)>MAX_WAIT_TIME) //
	{
		HAL_TIM_Base_Stop_IT(ginf_htim);
		if (gInf_State.syn_flag == 1)
		{
			//������������, ��һ��differΪͬ����,y�Ͻ��Ĵ�����Ҫ������У��
			for(j=0;j<4;j++)
			{
				for(k=0;k<8;k++)
				{
					if(((DATA_L-ERROR_TIME)<=gInf_State.differ_time[1+j*8+k])
						&&(gInf_State.differ_time[1+j*8+k] <= (DATA_L+ERROR_TIME))) //0 �������
					{
						inf_data[j] &= ~(1<<k); //0

					}
					else if(((DATA_H-ERROR_TIME)<=gInf_State.differ_time[1+j*8+k]) //1�������
						&&(gInf_State.differ_time[1+j*8+k] <= (DATA_H+ERROR_TIME)))
					{
						inf_data[j] |= (1<<k); //1

					}
					else
					{
						LOG("ERROR,%d,%d\r\n",DATA_H-TIME_UNIT,DATA_H+TIME_UNIT);
					}
				}
			}
			//LOG("addr=0x%02X,addr_f=0x%02X,con=0x%02X,con=0x%02X\r\n",inf_data[0],inf_data[1],inf_data[2],inf_data[3]);
			*addr = inf_data[0];
			*cmd = inf_data[2];
			ret = 1;

		}
		else
		{
			LOG("no syn flag ,no data\r\n");
		}
		memset(&gInf_State,0,sizeof(gInf_State));
	}

	return ret;
}

uint8_t Test_Inf_Receiver(void)
{
	char i=0,j=0,k=0;
	uint8_t inf_data[4]={0};
	uint8_t ret = 0;

	if((gInf_State.all_time-gInf_State.last_data_time)>MAX_WAIT_TIME) //
	{
		HAL_TIM_Base_Stop_IT(ginf_htim);
		LOG("inf data finsh\r\n");
		for(i=0;i<32;i++)
		{
			//LOG("a=%d\r\n",gInf_State.differ_time[i]);
		}
		
		if (gInf_State.syn_flag == 1)
		{
			LOG("Geted syn flag ,have data\r\n");
			//������������, ��һ��differΪͬ����
			for(j=0;j<4;j++)
			{
				for(k=0;k<8;k++)
				{
					//LOG("differ[%d]=%d\r\n",1+j*8+k,gInf_State.differ_time[1+j*8+k]);
					if(((DATA_L-ERROR_TIME)<=gInf_State.differ_time[1+j*8+k])
						&&(gInf_State.differ_time[1+j*8+k] <= (DATA_L+ERROR_TIME))) //0 �������
					{
						inf_data[j] &= ~(1<<k); //0
						//LOG("0\r\n");
					}
					else if(((DATA_H-ERROR_TIME)<=gInf_State.differ_time[1+j*8+k]) //1�������
						&&(gInf_State.differ_time[1+j*8+k] <= (DATA_H+ERROR_TIME)))
					{
						inf_data[j] |= (1<<k); //1
						//LOG("1\r\n");
					}
					else
					{
						LOG("ERROR,%d,%d\r\n",DATA_H-TIME_UNIT,DATA_H+TIME_UNIT);
					}
				}
			}
			
			LOG("addr=0x%02X,addr_f=0x%02X,con=0x%02X,con=0x%02X\r\n",inf_data[0],inf_data[1],inf_data[2],inf_data[3]);
			ret = 1;
		}
		else
		{
			LOG("no syn flag ,no data\r\n");
		}
		memset(&gInf_State,0,sizeof(gInf_State));
	}

	return ret;
}



