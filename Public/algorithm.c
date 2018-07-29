#include "algorithm.h"
#include "LQueue.h"


/************************************************

自己设计的波形峰值和频率计算算法
其原理概括为：输入一个队列的波形坐标数据
依据波形的两个上升沿判断周期大小从而计算出频率
一句波形的最高点计算出波形峰值

*************************************************/
float Freq_Value;//频率值
float Vol_Value;//峰值电压
float Freq_Symbol;//频率坐标象征值（需转化为频率值）
float Vol_Symbol;//峰值电压坐标象征值
int num=0;//用于记录一个峰值点到下一个峰值点的坐标隔距（用于计算频率）
float a,b;//记录两个峰值点横坐标
float precision;//精度（显示屏一个点所代表的时间，单位为秒）
float Freq_Term[500]={0};//记录电压每一个周期的频率值（最后求平均）
float Vol_Term[500]={0};//记录电压所有峰值（最后求平均）
float Low_Vol=0;//低峰电压值
float Low_Vol_Symbol=35;//低峰电压象征值
int j=0,k=0;
int i;
void Get_Vol_Freq(LQueue *Q)
{
	//初始化数据
	extern int flag;//flag代表当前精度挡位
	Node *q=Q->front;
	Freq_Symbol=0;
	Vol_Symbol=0;
	k=0,j=0;
	a=0,b=0; 
	num=0;

	
	while(q->next!=NULL)
	{
		//下降沿
		while(q->next->data - q->data>=0&&q->next!=NULL)
		{
			q=q->next;
//			printf("%f   ",q->data);
			if(q->data>Low_Vol_Symbol)
			{
				Low_Vol_Symbol=q->data;
			}
			num++;
		}
		a=q->data;//记录该周期最低峰值点
		//上升沿
		while(q->next->data - q->data<=0&&q->next!=NULL)
		{
			q=q->next;
			if(q->data>Low_Vol_Symbol)
			{
				Low_Vol_Symbol=q->data;
			}
//			printf("%f   ",q->data);
			num++;

		}
		b=q->data;//记录该周期最高峰值点
		if(a-b>10)//如果两个点坐标差大于10，则判定为有效峰，执行记录（因为该差若小于10，则可能是寻常电压抖动，）
		{
			Freq_Term[k++]=num;	
			num=0;			
			Vol_Term[j++]=q->data;

		}
	}
//	printf("         %f   ",Low_Vol);
	for(i=1;i<k-1;i++)
		Freq_Symbol+=Freq_Term[i]/(float)(k-2);//求平均
//	printf("%f   ",Freq_Symbol);
	for(i=0;i<j;i++)
		Vol_Symbol+=Vol_Term[i]/(float)k;
//	printf("%f  ",Vol_Symbol);

	switch(flag)//精度判断
	{
		case 0:precision=0.0001;break;
		case 1:precision=0.0002;break;
		case 2:precision=0.0004;break;
		case 3:precision=0.0008;break;
		case 4:precision=0.0016;break;
		case 5:precision=0.0032;break;
	}
	Freq_Value=1.0/(precision*Freq_Symbol);//转换为频率单位（Hz）
	if(Vol_Symbol>20&&Vol_Symbol<300)
		Vol_Value=(217.0-Vol_Symbol)/50.0;//转换为常见电压单位（V）
	Low_Vol=(217.0-Low_Vol_Symbol)/50.0;//转换为常见电压单位（V）

}

