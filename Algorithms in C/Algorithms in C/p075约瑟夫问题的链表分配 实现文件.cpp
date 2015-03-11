#include <stdlib.h>
#include "p075约瑟夫问题的链表分配.h"

	// 分配一个Node数组, 前一个Node的next指向后一个

link freeList;
void initNodes(int N)
{
	int i;
	freeList = (link)malloc((N + 1) * sizeof(*freeList));
	for (i = 0; i < N; i++)	// 这里把书上的N+1改成了N
		freeList[i].next = &freeList[i+1];
	freeList[N].next = NULL;
}

	// 取出初始化链表第二个node, 赋值为参数, next指向自己
link newNode(int i)
{
	link x = deleteNext(freeList);
	x->item = i;
	x->next = x;
	return x;
}

	// 删除参数link指向的节点的下一个节点, 并将这个被删除的节点返回
link deleteNext(link Current)
{
	link Next = Current->next;
	Current->next = Next->next;
	return Next;
}

	// 在第一个参数link指向的node后边加入第二个参数link指向的node
void insertNext(link Prev, link insert)
{
	insert->next = Prev->next;
	Prev->next = insert;
}

	// 返回参数link指向的node后边的node
link Next(link x)
{
	return x->next;
}

	// 返回参数link指向node的item值
int Item(link x)
{
	return x->item;
}

	// 将被删除的node与freeList链接
void freeNode(link x)
{
	insertNext(freeList, x);
}