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
* 函 数 名         : main
* 函数功能		   : 主函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
int main()
{
	extern LQueue *Q1;     														//引用Q1 原定义在bsp_exti.c
	Q1 = (LQueue *)malloc(sizeof(LQueue));
	InitLQueue(Q1);
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);   //中断优先级分组 分2组
  USART1_Config();                         				
	ADC1_Init();       														    //AD初始化
	TFTLCD_Init();																   	//LCD初始化
	LED_Init();
	KEY_Init();
	My_EXTI_Init();  																	//外部中断初始化
	FRONT_COLOR=BLACK;																//屏幕底色为黑
	Write_Chart(0);																		//初始图表绘制
while(1)
{
		led1=!led1;																			//生命指示灯 一闪一闪则代表程序还没炸
		delay_ms(1000);	
}

	
	
	
	
	
	
	
}

