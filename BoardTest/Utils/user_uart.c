#include "user_uart.h"
#include "common.h"


extern UART_HandleTypeDef huart1;//普通串口
extern UART_HandleTypeDef huart2;//普通串口
extern UART_HandleTypeDef huart3; //RS485

//485接收发送使能端
#define RS485_PIN GPIO_PIN_1
#define RS485_GPIO_PROT GPIOC


//串口缓存
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
*开启一次中断接收
*/
void init_uart_uart(void)
{
	//开启一次中断接收,如果在接收到数据后，会调用HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle) 函数
	//所以只需要在HAL_UART_RxCpltCallback 中处理数据
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
*使用uart3和PC1
*/
void Init_Rs485(void)
{
	HAL_UART_Receive_IT(&huart3,(uint8_t *)&guart3_temp_value,1);
	HAL_GPIO_WritePin(RS485_GPIO_PROT, RS485_PIN, GPIO_PIN_RESET);//PC1 使能接收
}

/**
*设置使能脚
*/
void Set_Rs485_RW_State(Rs485State state)
{
	if(state == RS485_STATE_R)
	{
		HAL_GPIO_WritePin(RS485_GPIO_PROT, RS485_PIN, GPIO_PIN_RESET);//PC1 使能接收
	}
	else
	{
		HAL_GPIO_WritePin(RS485_GPIO_PROT, RS485_PIN, GPIO_PIN_SET);//PC1 使能发送
	}

}

/**
*Rs485发送数据
*/
uint8_t Rs485_Send_Data(uint8_t *data, uint8_t len)
{
	uint8_t ret =0;
	HAL_GPIO_WritePin(RS485_GPIO_PROT, RS485_PIN, GPIO_PIN_SET);//PC1 使能发送
	uartWrite(&huart3, data, len);
	Delay_Us(100);
	HAL_GPIO_WritePin(RS485_GPIO_PROT, RS485_PIN, GPIO_PIN_RESET);//PC1 使能接收
	return ret;
}

/**
*数据接收中断回调函数
*在usart.h 中申明了,没有实现
*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart == &huart1) //如果是串口1
	{
		if(guart1_recvied_len<UART1_RECEIVE_CACHE_LEN) //把数据保存在缓存里
		{
			guart1_cache_buf[guart1_recvied_len++]=guart1_temp_value;
		}
		HAL_UART_Receive_IT(huart,(uint8_t *)&guart1_temp_value,1); //重新调用中断接收函数
	}
	if (huart == &huart2) //如果是串口2
	{
		if(guart2_recvied_len<UART2_RECEIVE_CACHE_LEN) //把数据保存在缓存里
		{
			guart2_cache_buf[guart2_recvied_len++]=guart2_temp_value;
		}
		HAL_UART_Receive_IT(huart,(uint8_t *)&guart2_temp_value,1);
	}
	if (huart == &huart3) //如果是串口3
	{
		if(guart3_recvied_len<UART3_RECEIVE_CACHE_LEN) //把数据保存在缓存里
		{
			guart3_cache_buf[guart3_recvied_len++]=guart3_temp_value;
		}
		HAL_UART_Receive_IT(huart,(uint8_t *)&guart3_temp_value,1);
	}
}

/**
*检测串口1的数据
* 需要有个判断标准，用来判断协议是否完成
* 双方也需要有一定的延迟
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

