#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "tftlcd.h"
#include "out.h"
#include <math.h>
#include "dac.h"
void Out_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//定义结构体变量
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;  //选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //设置推挽输出模式
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //设置传输速率
	GPIO_Init(GPIOC,&GPIO_InitStructure); 	   /* 初始化GPIO */
}

/**
* 输出形式为方形波
*
*/
void Output_Square(void)
{
	  Vol_out=0;
		delay_ms(10);
		Vol_out=1;
		delay_ms(10);
		Vol_out=0;
		delay_ms(10);
		Vol_out=1;
		delay_ms(10);
}
/**
* 输出形式为正弦波
*
*/

void Output_Sin(const u8 point,u16 maxnum)
{
/*u8 i=0; 
//int dac_value=0;               //不知道如何将sin_tab给DA输出
u16 dacval;
float dac_vol;
float sin_tab[50];
float x;   //弧度
float jiao;//角度 分度角
jiao=360.000/point; 

  for(i=0;i<point;i++)
{
			x=jiao*i;    //得到角度值
			x=x*0.01744; //角度转弧度  弧度=角度*（π/180）
      sin_tab[i]=(maxnum/2)*sin(x)+(maxnum/2);
}*/
}

/**
* 输出形式为三角形波
*
*/
void Output_Triangle(void)   //三角波dac.c文件和main里面的初始化和使能
{
	
}