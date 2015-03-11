// 程序清单17.7
#include <stdio.h>
#include <stdlib.h>
#include "p504接口_队列.h"

// 局部函数
static void CopyToNode (Item item, Node * pn);
static void CopyToItem (Node * pn, Item * pi);

// 初始化队列
void InitializeQueue (Queue * pq)
{
	pq->front = pq->rear = NULL;
	pq->items = 0;
}

bool QueueIsFull (const Queue * pq)
{
	return pq->items == MAXQUEUE;  // 逻辑判断, 结果为true或false
}

bool QueueIsEmpty (const Queue * pq)
{
	return pq->items == 0;
}

int QueueItemCount (const Queue * pq)
{
	return pq->items;
}

bool EnQueue (Item item, Queue  * pq)
{
	Node * pnew;
	if (QueueIsFull (pq))
		return false;
	pnew = (Node *) malloc (sizeof (Node));
	if (pnew == NULL)
	{
		fprintf (stderr, "Unable to allocate memory!\n");
		exit (1);
	}
	CopyToNode (item, pnew);
	pnew->next = NULL;
	if (QueueIsEmpty(pq))
		pq->front = pnew;      // 项目位于队列首端
	else
		pq->rear->next = pnew; // 链接到队列尾端
	pq->rear = pnew;           // 记录队列尾端的位置
	pq->items++;               // 队列项目个数增1

	return true;
}

static void CopyToNode (Item item, Node * pn)
{
	pn->item = item;
}

bool DeQueue (Item * pitem, Queue * pq)
{
	Node * pt;

	if (QueueIsEmpty (pq))
		return false;
	CopyToItem (pq->front, pitem);
	pt = pq->front;
	pq->front = pq->front->next;
	free (pt);
	pq->items--;
	if (pq->items == 0)
		pq->rear = NULL;

	return true;
}

static void CopyToItem (Node * pn, Item * pi)
{
	*pi = pn->item;
}

void EmptyTheQueue (Queue * pq)
{
	Item dummy;
	while (!QueueIsEmpty (pq))
		DeQueue (&dummy, pq);
}