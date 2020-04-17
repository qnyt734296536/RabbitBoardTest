#include "user_uart.h"
#include "common.h"


extern UART_HandleTypeDef huart1;//��ͨ����
extern UART_HandleTypeDef huart2;//��ͨ����
extern UART_HandleTypeDef huart3; //RS485

//485���շ���ʹ�ܶ�
#define RS485_PIN GPIO_PIN_1
#define RS485_GPIO_PROT GPIOC


//���ڻ���
uint8_t guart1_cache_buf[UART1_RECEIVE_CACHE_LEN];
uint8_t guart2_cache_buf[UART1_RECEIVE_CACHE_LEN];
uint8_t guart3_cache_buf[UART1_RECEIVE_CACHE_LEN];

uint16_t guart1_recvied_len = 0;
uint16_t guart2_recvied_len = 0;
uint16_t guart3_recvied_len = 0;

uint8_t guart1_temp_value =0;
uint8_t guart2_temp_value =0;
uint8_t guart3_temp_value =0;




/**
*����һ���жϽ���
*/
void init_uart_uart(void)
{
	//����һ���жϽ���,����ڽ��յ����ݺ󣬻����HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle) ����
	//����ֻ��Ҫ��HAL_UART_RxCpltCallback �д�������
	HAL_UART_Receive_IT(&huart1,(uint8_t *)&guart1_temp_value,1);
	HAL_UART_Receive_IT(&huart2,(uint8_t *)&guart2_temp_value,1);
	
}



int32_t uartWrite(UART_HandleTypeDef *huart,uint8_t *buf, uint32_t len)
{
  uint32_t i = 0;
	if(NULL == buf)
	{
			return -1;
	}
	for(i=0; i<len; i++)
	{
			HAL_UART_Transmit_IT(huart, (uint8_t *)&buf[i], 1);
			while (huart->gState != HAL_UART_STATE_READY);
	}
		return 0;
}  




/**
*ʹ��uart3��PC1
*/
void Init_Rs485(void)
{
	HAL_UART_Receive_IT(&huart3,(uint8_t *)&guart3_temp_value,1);
	HAL_GPIO_WritePin(RS485_GPIO_PROT, RS485_PIN, GPIO_PIN_RESET);//PC1 ʹ�ܽ���
}

/**
*����ʹ�ܽ�
*/
void Set_Rs485_RW_State(Rs485State state)
{
	if(state == RS485_STATE_R)
	{
		HAL_GPIO_WritePin(RS485_GPIO_PROT, RS485_PIN, GPIO_PIN_RESET);//PC1 ʹ�ܽ���
	}
	else
	{
		HAL_GPIO_WritePin(RS485_GPIO_PROT, RS485_PIN, GPIO_PIN_SET);//PC1 ʹ�ܷ���
	}

}

/**
*Rs485��������
*/
uint8_t Rs485_Send_Data(uint8_t *data, uint8_t len)
{
	uint8_t ret =0;
	HAL_GPIO_WritePin(RS485_GPIO_PROT, RS485_PIN, GPIO_PIN_SET);//PC1 ʹ�ܷ���
	uartWrite(&huart3, data, len);
	Delay_Us(100);
	HAL_GPIO_WritePin(RS485_GPIO_PROT, RS485_PIN, GPIO_PIN_RESET);//PC1 ʹ�ܽ���
	return ret;
}

/**
*���ݽ����жϻص�����
*��usart.h ��������,û��ʵ��
*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart == &huart1) //����Ǵ���1
	{
		if(guart1_recvied_len<UART1_RECEIVE_CACHE_LEN) //�����ݱ����ڻ�����
		{
			guart1_cache_buf[guart1_recvied_len++]=guart1_temp_value;
		}
		HAL_UART_Receive_IT(huart,(uint8_t *)&guart1_temp_value,1); //���µ����жϽ��պ���
	}
	if (huart == &huart2) //����Ǵ���2
	{
		if(guart2_recvied_len<UART2_RECEIVE_CACHE_LEN) //�����ݱ����ڻ�����
		{
			guart2_cache_buf[guart2_recvied_len++]=guart2_temp_value;
		}
		HAL_UART_Receive_IT(huart,(uint8_t *)&guart2_temp_value,1);
	}
	if (huart == &huart3) //����Ǵ���3
	{
		if(guart3_recvied_len<UART3_RECEIVE_CACHE_LEN) //�����ݱ����ڻ�����
		{
			guart3_cache_buf[guart3_recvied_len++]=guart3_temp_value;
		}
		HAL_UART_Receive_IT(huart,(uint8_t *)&guart3_temp_value,1);
	}
}

/**
*��⴮��1������
* ��Ҫ�и��жϱ�׼�������ж�Э���Ƿ����
* ˫��Ҳ��Ҫ��һ�����ӳ�
*/
void check_uart_data(void)
{
		
		if(guart1_recvied_len>=10)
		{
			uartWrite(&huart1, (uint8_t*)guart1_cache_buf, guart1_recvied_len);
			guart1_recvied_len = 0;
		}

		if(guart2_recvied_len >=10)
		{
			uartWrite(&huart2, (uint8_t*)guart2_cache_buf, guart1_recvied_len);
			guart2_recvied_len=0;
		}
}

uint8_t Check_Rs485_data(void)
{
	uint8_t ret = 0;
	if(guart3_recvied_len>=10)
	{
		Rs485_Send_Data((uint8_t*)guart3_cache_buf, guart3_recvied_len);
		guart3_recvied_len=0;
		ret = 1;
	}
	
	return ret;

}

