// 程序清单 17.6
#pragma c9x on
#ifndef _QUE_H_
#define _QUE_H_

// 在此插入item类型的定义
typedef int Item;

#define MAXQUEUE 10

typedef struct node
{
	struct node * next;
	Item item;
}Node;

typedef struct queue
{
	Node * front;  // 指向队列首指针
	Node * rear;   // 指向队列尾指针
	int items;     // 队列中项目的个数
}Queue;

void InitializeQueue(Queue * pq);

bool QueueIsFull(const Queue * pq);

bool QueueIsEmpty(const Queue * pq);

int QueueItemCount(const Queue * pq);

bool EnQueue(Item item, Queue * pq);

bool DeQueue(Item * pitem, Queue * pq);

void EmptyTheQueue(Queue * pq);

#endif