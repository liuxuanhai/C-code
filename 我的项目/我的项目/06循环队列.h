// 数组实现 循环队列 对于队列总长固定的数据类型有用
const int MAXSIZE = 10;
typedef int QElemType;
typedef struct
{
	QElemType data[MAXSIZE];
	int front;	// 头指针
	int rear;	// 尾指针	若队列不为空 指向队列尾元素的下一个位置
}SqQueue;

// 初始化一个队列
bool InitQueue(SqQueue * Q)
{
	Q->front	= 0;
	Q->rear		= 0;
	return true;
}

// 求队列的长度
int QueueLength(SqQueue Q)
{
	return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}

// 如果队列未满, 则插入元素e为Q新的队尾元素
bool EnQueue(SqQueue * Q, QElemType e)
{
	if ((Q->rear + 1) % MAXSIZE == Q->front)	// 队列满的判断
		return false;
	Q->data[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXSIZE;	// rear 指针向后移动一位, 若到了最后, 则转向数组头部
	return true;
}

bool DeQueue(SqQueue * Q, QElemType * e)
{
	if (Q->front == Q->rear)	// 队列为空
		return false;
	*e = Q->data[Q->front];
	Q->front = (Q->front + 1) % MAXSIZE;	// front 指针向后移动一个位置, 如果到了最后, 则转到数组头部
	return true;
}

#include <iostream>
void ShowQueue(const SqQueue * Q)
{
	if (Q->front == Q->rear)	// 队列为空
		std::cout << "队列是空的!\n";
	for (int i = Q->front;  i != Q->rear; i = ++i % MAXSIZE)
		std::cout << Q->data[i] << " ";
	std::cout << std::endl;
}