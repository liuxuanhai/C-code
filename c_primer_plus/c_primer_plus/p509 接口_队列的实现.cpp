// 程序清单 17.7
#include <stdio.h>
#include <stdlib.h>
#include "p504 接口_队列.h"

static void CopyToNode(Item item, Node * pn);
static void CopyToItem(Node * pn, Item * pi);

void InitializeQueue(Queue * pq)
{
	pq->front = NULL;
	pq->rear = NULL;
	pq->items = 0;
}

bool QueueIsFull(const Queue * pq)
{
	return pq->items == MAXQUEUE;
}

bool QueueIsEmpty(const Queue * pq)
{
	return pq->items == 0;
}

int QueueItemCount(const Queue * pq)
{
	return pq->items;
}

bool EnQueue(Item item, Queue * pq)
{
	if (QueueIsFull(pq))
		return false;
	
	Node * pnew = (Node *)malloc(sizeof(Node));
	if (pnew == NULL)
	{
		printf("Unable to allocate memory!\n");
		exit(1);
	}
	CopyToNode(item, pnew);
	pnew->next = NULL;
	if (QueueIsEmpty(pq))  // 项目位于队列首端
		pq->front = pnew;
	else
		pq->rear->next = pnew;
	pq->rear = pnew;
	pq->items++;

	return true;
}

static void CopyToNode(Item item, Node * pn)
{
	pn->item = item;
}

bool DeQueue(Item * pitem, Queue * pq)
{
	Node * pt;
	if (QueueIsEmpty(pq))
		return false;
	CopyToItem(pq->front, pitem);
	pt = pq->front;
	pq->front = pq->front->next;
	free(pt);
	pq->items--;
	if (pq->items == 0)
		pq->rear = NULL;
	return true;
}

static void CopyToItem(Node * pn, Item * pi)
{
	*pi = pn->item;
}

void EmptyTheQueue(Queue * pq)
{
	Item dummy;
	while (!QueueIsEmpty(pq))
		DeQueue(&dummy, pq);
}