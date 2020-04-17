#include "delay.h"

static uint8_t fac_us = 0; //us��ʱ������
static uint16_t fac_ms = 0; //ms��ʱ������,����ÿ�����ĵ�ms��

//��ʼ���ӳٺ���
//SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
//SYSCLK:ϵͳʱ��
void Delay_Init(uint8_t SYSCLK)
{
    SysTick->CTRL &= ~(1 << 2); //SYSTICKʹ���ⲿʱ��Դ
    fac_us = SYSCLK / 8;    //�����Ƿ�ʹ��ucos,fac_us����Ҫʹ��
    fac_ms = (uint16_t)fac_us * 1000; //��ucos��,����ÿ��ms��Ҫ��systickʱ����
}

//��ʱnus
//nusΪҪ��ʱ��us��.
void Delay_Us(uint32_t nus)
{
    uint32_t temp;
    SysTick->LOAD = nus * fac_us; //ʱ�����
    SysTick->VAL = 0x00;      //��ռ�����
    SysTick->CTRL = 0x01 ;    //��ʼ����
    do
    {
        temp = SysTick->CTRL;
    }
    while ((temp & 0x01) && !(temp & (1 << 16))); //�ȴ�ʱ�䵽��
    SysTick->CTRL = 0x00;     //�رռ�����
    SysTick->VAL = 0X00;      //��ռ�����
}
//��ʱnms
//ע��nms�ķ�Χ
//SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK��λΪHz,nms��λΪms
//��72M������,nms<=1864
void Delay_Ms(uint16_t nms)
{
    uint32_t temp;
    SysTick->LOAD = (uint32_t)nms * fac_ms; //ʱ�����(SysTick->LOADΪ24bit)
    SysTick->VAL = 0x00;          //��ռ�����
    SysTick->CTRL = 0x01 ;        //��ʼ����
    do
    {
        temp = SysTick->CTRL;
    }
    while ((temp & 0x01) && !(temp & (1 << 16))); //�ȴ�ʱ�䵽��
    SysTick->CTRL = 0x00;     //�رռ�����
    SysTick->VAL = 0X00;      //��ռ�����
}
















































