#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "stm32f10x.h"
#include "bsp_adc.h"
#define MAXQUEUE 100

//��ʽ���нṹ
typedef struct node
{
    float data;                   //������ָ��
    struct node *next;            //ָ��ǰ������һ���
} Node;

typedef struct Lqueue
{
    Node *front;                   //��ͷ
    Node *rear;                    //��β
    size_t data_size;            //�������ڴ��С
} LQueue;

typedef enum
{
    FLASE=0, TRUE=1
} Status;

void InitLQueue(LQueue *Q);
void DestoryLQueue(LQueue *Q);
Status IsEmptyLQueue(const LQueue *Q);
Status GetHeadLQueue(LQueue *Q, float *e);
int LengthLQueue(LQueue *Q);
Status EnLQueue(LQueue *Q, float data);
void PreEnLQueue(LQueue *Q, float data);
Status DeLQueue(LQueue *Q);
void RearDeLQueue(LQueue *Q);
void ClearLQueue(LQueue *Q);
Status TraverseLQueue(const LQueue *Q,u16 COLOR,int Move,void (*foo)(float q,int num,float pre,u16 color));
void LPrint(float q,int num,float pre,u16 color);
void LPrint_2(float q,int num,float pre,u16 color);



#endif // QUEUE_H_INCLUDED


