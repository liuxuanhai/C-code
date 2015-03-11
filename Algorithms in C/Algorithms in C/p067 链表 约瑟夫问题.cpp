#include <stdio.h>
#include <stdlib.h>

typedef struct node * link;
typedef int	item;

struct node
{
	item Item;
	link next;
};

int main(void)
{
	int M, N;

	printf("人数: ");
	scanf("%d", &N);
	printf("偏移量: ");
	scanf("%d", &M);

		// 创建第一个节点, 以便在循环中使用
	link headnode	= (link)malloc(sizeof(node));
	headnode->Item = 1;
	headnode->next = headnode;	// 形成循环链表

		// 临时链接指向操作节点(第一个节点);
	link temp		= headnode;

		// 创建剩余节点
	for (int i = 2; i <= N; i++)
	{
			// 操作节点next指向新节点
		temp->next	= (link)malloc(sizeof(node));

			// 新节点成为操作节点
		temp		= temp->next;

			// 对操作节点进行赋值
		temp->Item	= i;
		temp->next	= headnode;	// 形成循环链表
	}

		// 这里的逻辑与书上稍微有点不同, 这里temp初始指向的是头, 而书中x指向的是尾
	temp = headnode;
	while (temp->next != temp)
	{
		for (int i = 1; i < M - 1; i++)
			temp = temp->next;
		temp->next = temp->next->next;	// 移除目标节点
		temp = temp->next;	// 指向移除点的下一个node
		N--;
	}
	printf("%d", temp->Item);

	return 0;
}