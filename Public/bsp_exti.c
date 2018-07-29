#include "exti.h"
#include "SysTick.h"
#include "key.h"
#include "LQueue.h"
#include "bsp_adc.h"
#include "tftlcd.h"
#include "write.h"
#include "algorithm.h"
#include <string.h>


LQueue *Q1;//定义队列
int move=0; //移动列数标记变量
int flag=0; //精度切换标记变量
/*******************************************************************************
* 函 数 名         : My_EXTI_Init
* 函数功能		   : 外部中断初始化
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void My_EXTI_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef  EXTI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource2);//选择GPIO管脚用作外部中断线路
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource3);//选择GPIO管脚用作外部中断线路
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource4);//选择GPIO管脚用作外部中断线路
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);//选择GPIO管脚用作外部中断线路
	
	
	//EXTI0 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//EXTI0中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
	
	//EXTI2 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//EXTI2中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
	
	//EXTI3 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//EXTI3中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
	//EXTI4 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//EXTI4中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
	
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
* 函 数 名         : EXTI0_IRQHandler
* 函数功能		   : 外部中断0函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void EXTI0_IRQHandler(void)
{
	flag=0;
	move=0;
	if(EXTI_GetITStatus(EXTI_Line0)==1)
	{
		u8 Freq_Value_String[10];//记录待输出字符串
		u8 Vol_Value_String[10];
		u8 Low_Value_String[10];
		u8 PP_Value_String[10];
		extern float Freq_Value;//引用
		extern float Vol_Value;
		extern float Low_Vol;
		float PP_Vol; //峰峰值电压（峰值-低峰值）
		u16 i;
		float y,yy;         							//y保存十进制电压值 yy保存该点屏幕y坐标
		extern u16 ADC_ConvertedValue;		//引用 原定义在bsp_adc
		ClearLQueue(Q1);
		if(K_UP==1)
		{
			led2=0;//指示灯
			//数据扫描
			for(i=1;i<1000;i++) 			
			{
				y=(float)((float)ADC_ConvertedValue/4096.0*3.3);					//数字量转换位十进制常见单位电压
				yy=182.0-(y/4.0*200.0)+35.0;//垂直坐标校准
				EnLQueue(Q1,yy);		//前入队
				delay_us(40);				//校准延时
			}
			Get_Vol_Freq(Q1);
//			printf("%f ",Freq_Value);
			PP_Vol=Vol_Value-Low_Vol;
			sprintf(Freq_Value_String,"%.2f",Freq_Value);//浮点类型转换为字符串类型
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
			TraverseLQueue(Q1,RED,0,LPrint);//遍历打印
			Write_Chart(flag);//绘表
			
		}	
		
	}
	EXTI_ClearITPendingBit(EXTI_Line0);
}

/*******************************************************************************
* 函 数 名         : EXTI3_IRQHandler
* 函数功能		   : 外部中断3函数
* 输    入         : 无
* 输    出         : 无
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
		u8 Freq_Value_String[10];//记录字符串
		u8 Vol_Value_String[10];
		u8 Low_Value_String[10];
		u8 PP_Value_String[10];
		extern float Freq_Value;//引用
		extern float Vol_Value;
		extern float Low_Value;
		float PP_Vol;
		float y,yy;
		extern u16 ADC_ConvertedValue;
		u16 i;
		ClearLQueue(Q1);//清空队列（单片机堆的限制很小，队列不能开很大，每次用完需要清空）
		if(K_DOWN==0)
		{	
			led2=1;
			for(i=1;i<1000;i++)
			{
				y=(float)((float)ADC_ConvertedValue/4096.0*3.3);					//数字量转换位十进制常见单位电压
				yy=182.0-(y/4.0*200.0)+35.0;//垂直坐标校准
				EnLQueue(Q1,yy);//前入队
				delay_us(40);//校准延时
				/*精度选择*/
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
			sprintf(Freq_Value_String,"%.2f",Freq_Value);//浮点类型转换为字符串类型
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
* 函 数 名         : EXTI2_IRQHandler
* 函数功能		   : 外部中断2函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2)==1)
	{
		delay_ms(10);
		if(K_LEFT==0)
		{
			led3=1;//指示灯
			TraverseLQueue(Q1,WHITE,move,LPrint_2);//定点清除
			move-=5;//图像向左移动五个像素点
			TraverseLQueue(Q1,RED,move,LPrint_2);//快速打印
			Write_Chart(flag);
		}
		
	}
	EXTI_ClearITPendingBit(EXTI_Line2);
}

/*******************************************************************************
* 函 数 名         : EXTI4_IRQHandler
* 函数功能		   : 外部中断4函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void EXTI4_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line4)==1)
	{
		delay_ms(10);
		if(K_RIGHT==0)
		{
			led3=0;
			TraverseLQueue(Q1,WHITE,move,LPrint_2); //定点清除
			move+=5;//图像向右移动5个像素点
			TraverseLQueue(Q1,RED,move,LPrint_2);//快速打印
			Write_Chart(flag);
		}
		
	}
	EXTI_ClearITPendingBit(EXTI_Line4);
}


