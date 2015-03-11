#include <stdio.h>
#include <stdlib.h>
#define 链表实现

#if defined 链表实现
typedef struct node * link;
struct node
{ 
	int item; 
	link next;
};

int main(void)
{
	int i, N, M;

	printf("初始圆周人数: ");
	scanf_s("%d", &N);
	printf("圆周指针偏移量: ");
	scanf_s("%d", &M);

		// 创建第一个节点
	link t = (link)malloc(sizeof *t);
	link x = t;

		// 给第一个节点赋值
	t->item = 1;	// 1 代表这是第一个节点
	t->next = t;	// 节点指向自己

		// 创建剩下的节点, 连成一个圆周
	for (i = 2; i <= N; i++)
	{
		x = (x->next = (link)malloc(sizeof *x));
		x->item = i; 
		x->next = t;
	}

		// 一直循环到只剩一个节点
	while (x != x->next)
	{
		for (i = 1; i < M; i++)
			x = x->next;
		x->next = x->next->next;
		N--;

		//	// 输出当前状态
		//link temp = x;
		//for (int i = 0; i < N; i++)
		//{
		//	printf("%d ", temp->item);
		//	temp = temp->next;
		//}
		//printf("\n");
	}
	printf("%d\n", x->item);
	return 0;
}

#else

#include <stdio.h>

int main(void)
{
	int i, N, M;

	printf("初始圆周人数: ");
	scanf_s("%d", &N);
	printf("圆周指针偏移量: ");
	scanf_s("%d", &M);

	int *item = (int *)malloc(sizeof(int) * N);
	for (i = 0; i < N; i++)
		item[i] = i + 1;
	item[N-1] = 0;

	while (item[i])
	{

	}

	return 0;
}

#endif