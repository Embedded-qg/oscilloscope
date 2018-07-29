#include "LQueue.h"
#include "tftlcd.h"
#include "stm32f10x.h"
#include "write.h"
/*********************************************

      队列基本操作函数封装 小心有诈

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
//销毁操作
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
//判断是否为空
Status IsEmptyLQueue(const LQueue *Q)
{
    if(Q->front->next == NULL)
        return TRUE;
    return FLASE;
}
//得到队列顶元素
Status GetHeadLQueue(LQueue *Q, float *e)
{
    if(IsEmptyLQueue(Q) == TRUE)
        return FLASE;
    *e = (Q->front->next->data);
    return TRUE;
}
//队列长度
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
//入队
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
//队头出队
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
//队尾出队
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
//清空队列
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
//遍历操作
Status TraverseLQueue(const LQueue *Q,u16 COLOR,int Move,void (*foo)(float q,int num,float pre,u16 color))
{
	int k=-300+Move;//-300为队列左右移动保留位
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
//带视觉效果打印（边打印边消除后三）
void LPrint(float q,int num,float pre,u16 color)
{
	if(num<300&&num>0)//屏幕边界保护
	{
		LCD_DrawFRONT_COLOR(num+20,q,color);//绘点
		LCD_DrawLine_Color(num+21,36,num+21,234,WHITE); //清楚后三列
		LCD_DrawLine_Color(num+22,36,num+22,234,WHITE);
		LCD_DrawLine_Color(num+23,36,num+23,234,WHITE);

		
		if(pre!=-1)//边界保护
		{
				LCD_DrawLine_Color(num+20,q,num+19,pre,color);//两点连线

		}
	}
}
//普通打印（快速完成）
void LPrint_2(float q,int num,float pre,u16 color)
{
	if(num<300&&num>0)//屏幕边界保护
	{
		LCD_DrawFRONT_COLOR(num+20,q,color);//绘点
		if(pre!=-1)//边界保护
		{
			LCD_DrawLine_Color(num+20,q,num+19,pre,color);//两点连线

		}
	}	
}





