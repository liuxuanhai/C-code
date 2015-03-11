// 程序清单 17.9
#pragma c9x on
#define _QUE_H_

// 在此插入item类型的定义
typedef struct item
{
	long arrive;  // 一位顾客加入队列的时间
	int processtime;  // 该顾客需要的咨询时间
}Item;

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

#include <stdio.h>
#include <stdlib.h>

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

#include <stdio.h>
#include <stdlib.h>  // rand() srand()
#include <time.h>    // time()
#define MIN_PER_HR 60.0

bool newcustomer(double x);  // 有新顾客到来吗?

Item custormertime(long when);  // 设置顾客参量

int main(void)
{
	Queue line;
	Item temp;    // 关于新顾客的数据
	int hours;    // 模拟的小时数
	int perhour;  // 每个小时顾客的平均数
	long cycle, cyclelimit;  // 循环计数器, 计数器的上界
	long turnaways = 0;   // 因队列已满被拒顾客数
	long customers = 0;   // 被加入队列的顾客数
	long served = 0;      // 在模拟期间得到服务的顾客数
	long sum_line = 0;    // 累计的队列长度
	int wait_time = 0;    // 从当前到Sigmund空闲的时间
	double min_per_cust;  // 顾客到来的平均间隔时间
	long line_wait = 0;   // 队列累计等待的时间

	InitializeQueue(&line);
	srand(time(0));  // 随机初始化rand()
	puts("Case Study: Sigmund Lander's Advice Booth");
	puts("Enter the number of simulation(模拟) hours: ");
	scanf("%d", &hours);
	cyclelimit = MIN_PER_HR * hours;
	puts("Enter the average number of customer per hour: ");
	scanf("%d", &perhour);
	min_per_cust = MIN_PER_HR / perhour;

	for (cycle = 0; cycle < cyclelimit; cycle++)  // 一次循环时一分钟的情况
	{
		if (newcustomer(min_per_cust))  // 如果有顾客到来
		{
			if (QueueIsFull(&line))  // 队列已满, 不能加入
				turnaways++;
			else  // 队列有空余, 可以加入
			{
				customers++;
				temp = custormertime(cycle);  // 存入队列新人的情况(咨询的时间, 来的时间) cycle是本顾客来时距离开始的分钟数
				EnQueue(temp, &line);  // 将新人加入队列中
			}
		}
		if (wait_time <= 0 && !QueueIsEmpty(&line))  // 如果sigmund空闲并且队列中有人在等待
		{
			DeQueue(&temp, &line);  // 把队首的人去除
			wait_time = temp.processtime;
			line_wait += cycle - temp.arrive;  // 现在的时间-来的时间就是现在正咨询的人等待的时间(咨询时候的时间不算做等待时间)
			served++;
		}
		if (wait_time > 0)  // 一次循环一分钟, 咨询的一分钟过去了
			wait_time--;
		sum_line += QueueItemCount(&line);  // 每一分钟的队列人数都加进去, 好求出平均每分钟队列出于多少人的状态
	}

	if (customers > 0)
	{
		printf("customers accepted: %ld\n", customers);
		printf("   customers served: %ld\n", served);  // customer - served 就是队列中等候的人的个数
		printf("      turnaways: %ld\n", turnaways);
		printf("average queue size: %.2f\n", (double)sum_line / cyclelimit);
		printf(" average wait time: %.2f minutes\n", (double)line_wait / served);
	}
	else
		puts("No customers!");
	EmptyTheQueue(&line);
	puts("Bye!");

	return 0;
}

// x是顾客到来的时间间隔(以秒计)
// 如果这一分钟内有顾客来, 则返回true
bool newcustomer(double x)
{
	if (rand() * x / RAND_MAX < 1)
		return true;
	else
		return false;
}

// when是顾客到来的时间
// 函数返回一个Item结构, 该结构的顾客到来时间设置为when
// 需要的咨询时间设置为一个范围在1-3之间的随机值
Item custormertime(long when)
{
	Item cust;

	cust.processtime = rand() % 3 + 1;
	cust.arrive = when;

	return cust;
}