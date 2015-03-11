#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node *link;
struct node
{
	int		iItem;
	link	next;
};

link reverse(link);

int main(void)
{
	srand((unsigned long)time(0));
	int N = 100;	// 项目个数

		// 生成一个链表, 内含无序整数

	link Current	= (link)malloc(sizeof (*Current));	// 哑节点
	link head		= Current;	// head链接哑节点
	Current->iItem = -1;
	Current->next	= NULL;
	for (int i = 0; i < N; i++)
	{
		link Prev	= Current;
		Current		= (link)malloc(sizeof (*Current));
		Current->iItem = rand() % 100;
		Current->next	= NULL;
		Prev->next	= Current;
	}

		// 输出未排序状态

	Current = head->next;	// 从哑节点后边开始输出
	while (Current != NULL)
	{
		printf("%d ", Current->iItem);
		Current = Current->next;
	}

		 // 开始进行插入排序

	link head2		= (link)malloc(sizeof(*head2));
	head2->next		= NULL;
	head2->iItem	= -2;

	link Next;
	for (Current = head->next, head->next = NULL; Current != NULL; Current = Next)
	{
		Next = Current->next;

		link Current2 = head2;
		for (; Current2->next != NULL; Current2 = Current2->next)
			if (Current2->next->iItem > Current->iItem)
				break;
		Current->next = Current2->next;
		Current2->next = Current;
	}

		// 输出排序后状态

	printf("\n\n\n");
	link Current2 = head2->next;	// 从哑节点后边开始输出
	while (Current2 != NULL)
	{
		static int i = 0;
		if (i++ == 100)
			break;
		printf("%d ", Current2->iItem);
		Current2 = Current2->next;
	}

		// 倒置链表

	printf("\n\n\n");
	Current2 = reverse(head2->next);	// 从哑节点后边开始输出
	while (Current2 != NULL)
	{
		static int i = 0;
		if (i++ == 100)
			break;
		printf("%d ", Current2->iItem);
		Current2 = Current2->next;
	}

	return 0;
}

link reverse(link CN)
{
	link NN, PN = NULL;	// NULL也可以当成一个node, 一个没有item的node
	while (CN != NULL)
	{
		NN			= CN->next;
		CN->next	= PN;
		PN			= CN;
		CN			= NN;
	}
	return PN;
}