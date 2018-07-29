#include "LQueue.h"
#include "tftlcd.h"
#include "stm32f10x.h"
#include "write.h"
/*********************************************

      ���л�������������װ С����թ

*********************************************/
void InitLQueue(LQueue *Q)
{
    Node *p = (Node *)malloc(sizeof(Node));
    
    Q->data_size = 4;
    Q->front = p;
    Q->front->next = NULL;
    Q->rear = p;
    Q->rear->next = NULL;
}
//���ٲ���
void DestoryLQueue(LQueue *Q)
{
    Node *p;
    while(Q->front != NULL)
    {
        p = Q->front;
        Q->front = Q->front->next;
    }
    Q->rear = NULL;
    free(Q);
    Q = NULL;
}
//�ж��Ƿ�Ϊ��
Status IsEmptyLQueue(const LQueue *Q)
{
    if(Q->front->next == NULL)
        return TRUE;
    return FLASE;
}
//�õ����ж�Ԫ��
Status GetHeadLQueue(LQueue *Q, float *e)
{
    if(IsEmptyLQueue(Q) == TRUE)
        return FLASE;
    *e = (Q->front->next->data);
    return TRUE;
}
//���г���
int LengthLQueue(LQueue *Q)
{
    int length = 0;
    Node *p = Q->front;
    while(p != NULL)
    {
        p = p->next;
        length++;
    }
    return length - 1;
}
//���
Status EnLQueue(LQueue *Q, float data)
{
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = data;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
    return TRUE;
}

void PreEnLQueue(LQueue *Q, float data)
{
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = data;
    p->next = Q->front;
    Q->front=p;
	
}
//��ͷ����
Status DeLQueue(LQueue *Q)
{
    Node *p;
    if(IsEmptyLQueue(Q) == TRUE)
        return FLASE;
    p = Q->front;
    Q->front = Q->front->next;
    free(p);
    p = NULL;
    return TRUE;
}
//��β����
void RearDeLQueue(LQueue *Q)
{
	Node *p,*q;
	p=Q->front;
	while(p->next->next!=NULL)
	{
		p=p->next;
	}
	q=p->next;
	p->next=NULL;
	Q->rear=p;
	free(q);
}
//��ն���
void ClearLQueue(LQueue *Q)
{
    Node *p;
    while(Q->front->next != NULL)
    {
        p = Q->front;
        Q->front = Q->front->next;
        free(p);
    }
    Q->rear = Q->front;
}
//��������
Status TraverseLQueue(const LQueue *Q,u16 COLOR,int Move,void (*foo)(float q,int num,float pre,u16 color))
{
	int k=-300+Move;//-300Ϊ���������ƶ�����λ
	float pre=-1;
    Node *q = NULL;
    q = Q->front->next;
    while(q != NULL)
    {			
        foo(q->data,k,pre,COLOR);
				pre = q->data;
        q = q->next;
				k++;
    }
    return TRUE;
}
//���Ӿ�Ч����ӡ���ߴ�ӡ������������
void LPrint(float q,int num,float pre,u16 color)
{
	if(num<300&&num>0)//��Ļ�߽籣��
	{
		LCD_DrawFRONT_COLOR(num+20,q,color);//���
		LCD_DrawLine_Color(num+21,36,num+21,234,WHITE); //���������
		LCD_DrawLine_Color(num+22,36,num+22,234,WHITE);
		LCD_DrawLine_Color(num+23,36,num+23,234,WHITE);

		
		if(pre!=-1)//�߽籣��
		{
				LCD_DrawLine_Color(num+20,q,num+19,pre,color);//��������

		}
	}
}
//��ͨ��ӡ��������ɣ�
void LPrint_2(float q,int num,float pre,u16 color)
{
	if(num<300&&num>0)//��Ļ�߽籣��
	{
		LCD_DrawFRONT_COLOR(num+20,q,color);//���
		if(pre!=-1)//�߽籣��
		{
			LCD_DrawLine_Color(num+20,q,num+19,pre,color);//��������

		}
	}	
}





