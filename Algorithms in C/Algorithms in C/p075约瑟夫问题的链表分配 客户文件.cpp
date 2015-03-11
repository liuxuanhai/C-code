#include <stdio.h>
#include "p075约瑟夫问题的链表分配.h"

int main(void)
{
	int i, N, M;

	printf_s("N: ");
	scanf_s ("%d", &N);
	printf_s("M: ");
	scanf_s ("%d", &M);

	Node t, x;

		// 为N个项目分配内存, 生成node数组;
	initNodes(N);

		// 取出一个node, 赋值为1, 只有一个node的循环链表
	link head = newNode(1);

		// 迭代出一个循环链表
	x = head;
	for (i = 2; i <= N; i++)
	{
		t = newNode(i);
		insertNext(x, t);
		x = t;
	}	// 此时x指向最后一个node, 在循环中x->next即是head

		// 输出链表的内容
	link Current = head;
	while (Current->next != head)
	{
		printf("%d ", Current->item);
		Current = Current->next;
	}
	printf("%d \n", Current->item);

	while (x != Next(x))
	{
		for (i = 1; i < M; i++)
			x = Next(x);
		freeNode(deleteNext(x));
	}
	printf("%d\n", Item(x));

	return 0;
}