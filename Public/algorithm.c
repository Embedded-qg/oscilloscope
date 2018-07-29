#include "algorithm.h"
#include "LQueue.h"


/************************************************

�Լ���ƵĲ��η�ֵ��Ƶ�ʼ����㷨
��ԭ�����Ϊ������һ�����еĲ�����������
���ݲ��ε������������ж����ڴ�С�Ӷ������Ƶ��
һ�䲨�ε���ߵ��������η�ֵ

*************************************************/
float Freq_Value;//Ƶ��ֵ
float Vol_Value;//��ֵ��ѹ
float Freq_Symbol;//Ƶ����������ֵ����ת��ΪƵ��ֵ��
float Vol_Symbol;//��ֵ��ѹ��������ֵ
int num=0;//���ڼ�¼һ����ֵ�㵽��һ����ֵ���������ࣨ���ڼ���Ƶ�ʣ�
float a,b;//��¼������ֵ�������
float precision;//���ȣ���ʾ��һ�����������ʱ�䣬��λΪ�룩
float Freq_Term[500]={0};//��¼��ѹÿһ�����ڵ�Ƶ��ֵ�������ƽ����
float Vol_Term[500]={0};//��¼��ѹ���з�ֵ�������ƽ����
float Low_Vol=0;//�ͷ��ѹֵ
float Low_Vol_Symbol=35;//�ͷ��ѹ����ֵ
int j=0,k=0;
int i;
void Get_Vol_Freq(LQueue *Q)
{
	//��ʼ������
	extern int flag;//flag����ǰ���ȵ�λ
	Node *q=Q->front;
	Freq_Symbol=0;
	Vol_Symbol=0;
	k=0,j=0;
	a=0,b=0; 
	num=0;

	
	while(q->next!=NULL)
	{
		//�½���
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
		a=q->data;//��¼��������ͷ�ֵ��
		//������
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
		b=q->data;//��¼��������߷�ֵ��
		if(a-b>10)//�����������������10�����ж�Ϊ��Ч�壬ִ�м�¼����Ϊ�ò���С��10���������Ѱ����ѹ��������
		{
			Freq_Term[k++]=num;	
			num=0;			
			Vol_Term[j++]=q->data;

		}
	}
//	printf("         %f   ",Low_Vol);
	for(i=1;i<k-1;i++)
		Freq_Symbol+=Freq_Term[i]/(float)(k-2);//��ƽ��
//	printf("%f   ",Freq_Symbol);
	for(i=0;i<j;i++)
		Vol_Symbol+=Vol_Term[i]/(float)k;
//	printf("%f  ",Vol_Symbol);

	switch(flag)//�����ж�
	{
		case 0:precision=0.0001;break;
		case 1:precision=0.0002;break;
		case 2:precision=0.0004;break;
		case 3:precision=0.0008;break;
		case 4:precision=0.0016;break;
		case 5:precision=0.0032;break;
	}
	Freq_Value=1.0/(precision*Freq_Symbol);//ת��ΪƵ�ʵ�λ��Hz��
	if(Vol_Symbol>20&&Vol_Symbol<300)
		Vol_Value=(217.0-Vol_Symbol)/50.0;//ת��Ϊ������ѹ��λ��V��
	Low_Vol=(217.0-Low_Vol_Symbol)/50.0;//ת��Ϊ������ѹ��λ��V��

}

