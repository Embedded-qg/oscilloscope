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
	GPIO_InitTypeDef GPIO_InitStructure;//����ṹ�����
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;  //ѡ����Ҫ���õ�IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //�����������ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //���ô�������
	GPIO_Init(GPIOC,&GPIO_InitStructure); 	   /* ��ʼ��GPIO */
}

/**
* �����ʽΪ���β�
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
* �����ʽΪ���Ҳ�
*
*/

void Output_Sin(const u8 point,u16 maxnum)
{
/*u8 i=0; 
//int dac_value=0;               //��֪����ν�sin_tab��DA���
u16 dacval;
float dac_vol;
float sin_tab[50];
float x;   //����
float jiao;//�Ƕ� �ֶȽ�
jiao=360.000/point; 

  for(i=0;i<point;i++)
{
			x=jiao*i;    //�õ��Ƕ�ֵ
			x=x*0.01744; //�Ƕ�ת����  ����=�Ƕ�*����/180��
      sin_tab[i]=(maxnum/2)*sin(x)+(maxnum/2);
}*/
}

/**
* �����ʽΪ�����β�
*
*/
void Output_Triangle(void)   //���ǲ�dac.c�ļ���main����ĳ�ʼ����ʹ��
{
	
}