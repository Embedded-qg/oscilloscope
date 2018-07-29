#include "exti.h"
#include "SysTick.h"
#include "key.h"
#include "LQueue.h"
#include "bsp_adc.h"
#include "tftlcd.h"
#include "write.h"
#include "algorithm.h"
#include <string.h>


LQueue *Q1;//�������
int move=0; //�ƶ�������Ǳ���
int flag=0; //�����л���Ǳ���
/*******************************************************************************
* �� �� ��         : My_EXTI_Init
* ��������		   : �ⲿ�жϳ�ʼ��
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void My_EXTI_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef  EXTI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource2);//ѡ��GPIO�ܽ������ⲿ�ж���·
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource3);//ѡ��GPIO�ܽ������ⲿ�ж���·
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource4);//ѡ��GPIO�ܽ������ⲿ�ж���·
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);//ѡ��GPIO�ܽ������ⲿ�ж���·
	
	
	//EXTI0 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//EXTI0�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	
	//EXTI2 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//EXTI2�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	
	//EXTI3 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//EXTI3�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	//EXTI4 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//EXTI4�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line2|EXTI_Line3|EXTI_Line4; 
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
}

/*******************************************************************************
* �� �� ��         : EXTI0_IRQHandler
* ��������		   : �ⲿ�ж�0����
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void EXTI0_IRQHandler(void)
{
	flag=0;
	move=0;
	if(EXTI_GetITStatus(EXTI_Line0)==1)
	{
		u8 Freq_Value_String[10];//��¼������ַ���
		u8 Vol_Value_String[10];
		u8 Low_Value_String[10];
		u8 PP_Value_String[10];
		extern float Freq_Value;//����
		extern float Vol_Value;
		extern float Low_Vol;
		float PP_Vol; //���ֵ��ѹ����ֵ-�ͷ�ֵ��
		u16 i;
		float y,yy;         							//y����ʮ���Ƶ�ѹֵ yy����õ���Ļy����
		extern u16 ADC_ConvertedValue;		//���� ԭ������bsp_adc
		ClearLQueue(Q1);
		if(K_UP==1)
		{
			led2=0;//ָʾ��
			//����ɨ��
			for(i=1;i<1000;i++) 			
			{
				y=(float)((float)ADC_ConvertedValue/4096.0*3.3);					//������ת��λʮ���Ƴ�����λ��ѹ
				yy=182.0-(y/4.0*200.0)+35.0;//��ֱ����У׼
				EnLQueue(Q1,yy);		//ǰ���
				delay_us(40);				//У׼��ʱ
			}
			Get_Vol_Freq(Q1);
//			printf("%f ",Freq_Value);
			PP_Vol=Vol_Value-Low_Vol;
			sprintf(Freq_Value_String,"%.2f",Freq_Value);//��������ת��Ϊ�ַ�������
			sprintf(Vol_Value_String,"%.2f",Vol_Value);
			sprintf(Low_Value_String,"%.2f",Low_Vol);
			sprintf(PP_Value_String,"%.2f",PP_Vol);
			LCD_ShowString(330,70,tftlcd_data.width,tftlcd_data.height,16,Vol_Value_String);
			LCD_ShowString(380,70,tftlcd_data.width,tftlcd_data.height,16,"V");
			LCD_ShowString(330,110,tftlcd_data.width,tftlcd_data.height,16,Low_Value_String);
			LCD_ShowString(380,110,tftlcd_data.width,tftlcd_data.height,16,"V");
			LCD_ShowString(330,150,tftlcd_data.width,tftlcd_data.height,16,PP_Value_String);
			LCD_ShowString(380,150,tftlcd_data.width,tftlcd_data.height,16,"V");
			LCD_ShowString(330,190,tftlcd_data.width,tftlcd_data.height,16,Freq_Value_String);	
			LCD_ShowString(380,190,tftlcd_data.width,tftlcd_data.height,16,"Hz");
			TraverseLQueue(Q1,RED,0,LPrint);//������ӡ
			Write_Chart(flag);//���
			
		}	
		
	}
	EXTI_ClearITPendingBit(EXTI_Line0);
}

/*******************************************************************************
* �� �� ��         : EXTI3_IRQHandler
* ��������		   : �ⲿ�ж�3����
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void EXTI3_IRQHandler(void)
{

	float PP_Vol;
	move=0;
	if(flag!=5)
		flag++;
	else 
		flag=0;
	if(EXTI_GetITStatus(EXTI_Line3)==1)
	{
		u8 Freq_Value_String[10];//��¼�ַ���
		u8 Vol_Value_String[10];
		u8 Low_Value_String[10];
		u8 PP_Value_String[10];
		extern float Freq_Value;//����
		extern float Vol_Value;
		extern float Low_Value;
		float PP_Vol;
		float y,yy;
		extern u16 ADC_ConvertedValue;
		u16 i;
		ClearLQueue(Q1);//��ն��У���Ƭ���ѵ����ƺ�С�����в��ܿ��ܴ�ÿ��������Ҫ��գ�
		if(K_DOWN==0)
		{	
			led2=1;
			for(i=1;i<1000;i++)
			{
				y=(float)((float)ADC_ConvertedValue/4096.0*3.3);					//������ת��λʮ���Ƴ�����λ��ѹ
				yy=182.0-(y/4.0*200.0)+35.0;//��ֱ����У׼
				EnLQueue(Q1,yy);//ǰ���
				delay_us(40);//У׼��ʱ
				/*����ѡ��*/
				switch(flag)
				{
					case 1:	delay_us(88);break;//10ms
					case 2: delay_us(267);break;//20ms
					case 3: delay_us(626);break;//40ms
					case 4: delay_us(1350);break;//80ms
					case 5: delay_us(2750);break;//160ms
				}
			}
			Get_Vol_Freq(Q1);
//			printf("%f ",Freq_Value);
			PP_Vol=Vol_Value-Low_Vol;
			sprintf(Freq_Value_String,"%.2f",Freq_Value);//��������ת��Ϊ�ַ�������
			sprintf(Vol_Value_String,"%.2f",Vol_Value);
			sprintf(Low_Value_String,"%.2f",Low_Vol);
			sprintf(PP_Value_String,"%.2f",PP_Vol);
			LCD_ShowString(330,70,tftlcd_data.width,tftlcd_data.height,16,Vol_Value_String);
			LCD_ShowString(380,70,tftlcd_data.width,tftlcd_data.height,16,"V");
			LCD_ShowString(330,110,tftlcd_data.width,tftlcd_data.height,16,Low_Value_String);
			LCD_ShowString(380,110,tftlcd_data.width,tftlcd_data.height,16,"V");
			LCD_ShowString(330,150,tftlcd_data.width,tftlcd_data.height,16,PP_Value_String);
			LCD_ShowString(380,150,tftlcd_data.width,tftlcd_data.height,16,"V");
			LCD_ShowString(330,190,tftlcd_data.width,tftlcd_data.height,16,Freq_Value_String);	
			LCD_ShowString(380,190,tftlcd_data.width,tftlcd_data.height,16,"Hz");
			TraverseLQueue(Q1,RED,0,LPrint);
			Write_Chart(flag);			
		}
		
	}
	EXTI_ClearITPendingBit(EXTI_Line3);
}

/*******************************************************************************
* �� �� ��         : EXTI2_IRQHandler
* ��������		   : �ⲿ�ж�2����
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2)==1)
	{
		delay_ms(10);
		if(K_LEFT==0)
		{
			led3=1;//ָʾ��
			TraverseLQueue(Q1,WHITE,move,LPrint_2);//�������
			move-=5;//ͼ�������ƶ�������ص�
			TraverseLQueue(Q1,RED,move,LPrint_2);//���ٴ�ӡ
			Write_Chart(flag);
		}
		
	}
	EXTI_ClearITPendingBit(EXTI_Line2);
}

/*******************************************************************************
* �� �� ��         : EXTI4_IRQHandler
* ��������		   : �ⲿ�ж�4����
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void EXTI4_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line4)==1)
	{
		delay_ms(10);
		if(K_RIGHT==0)
		{
			led3=0;
			TraverseLQueue(Q1,WHITE,move,LPrint_2); //�������
			move+=5;//ͼ�������ƶ�5�����ص�
			TraverseLQueue(Q1,RED,move,LPrint_2);//���ٴ�ӡ
			Write_Chart(flag);
		}
		
	}
	EXTI_ClearITPendingBit(EXTI_Line4);
}


