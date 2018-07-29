#include "out.h"
#include "stm32f10x.h"
#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "bsp_usart1.h"
#include "tftlcd.h"
#include "write.h"
#include "bsp_adc.h"
#include "dac.h"
#include "LQueue.h"
#include <stdlib.h>
#include <stdio.h>
#include "bsp_exti.h"
#include "bsp_led.h"
#include "bsp_key.h"
/*******************************************************************************
* �� �� ��         : main
* ��������		   : ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
int main()
{
	extern LQueue *Q1;     														//����Q1 ԭ������bsp_exti.c
	Q1 = (LQueue *)malloc(sizeof(LQueue));
	InitLQueue(Q1);
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);   //�ж����ȼ����� ��2��
  USART1_Config();                         				
	ADC1_Init();       														    //AD��ʼ��
	TFTLCD_Init();																   	//LCD��ʼ��
	LED_Init();
	KEY_Init();
	My_EXTI_Init();  																	//�ⲿ�жϳ�ʼ��
	FRONT_COLOR=BLACK;																//��Ļ��ɫΪ��
	Write_Chart(0);																		//��ʼͼ�����
while(1)
{
		led1=!led1;																			//����ָʾ�� һ��һ����������ûը
		delay_ms(1000);	
}

	
	
	
	
	
	
	
}

