#include "p075 约瑟夫问题的链表分配.h"
#include <stdio.h>
#define N  9
#define M  5
int main(void)
{
		// 为N个项目分配内存, 生成空闲数组
	initNode(N);

		// 取出一个node, 赋值为1, node的next为NULL
	link head = newNode(1);

		// 迭代出一个循环链表
	link CN;
	link PN = head;
	for (int i = 2; i <= N; i++)
	{
		CN = newNode(i);
		insertNode(PN, CN);
		PN = CN;
	}
	CN->next = head;	// 形成循环链表
	link Last = CN;

		// 输出链表的内容

	CN = head;
	while (CN->next != head)
	{
		printf("%d ", CN->item);
		CN = CN->next;
	}
	printf("%d \n", CN->item);

	CN = Last;
	while (CN != CN->next)
	{
		for (int i = 1; i < M; i++)
			CN = CN->next;
		printf("%d\n", CN->next->item);
		freeNode(deleteNext(CN));
	}

	printf("\n\n%d \n", CN->item);

	return 0;
}