#include "p075 约瑟夫问题的链表分配.h"
#include <stdlib.h>

	// 空闲链表初始化:
	//		. 空闲链表有自己的哑节点
	//		. 空闲链表的表头链接应该可以被各个函数共享
	//		. 空闲链表的前node链接着后node
	//		. 空闲链表的最终逻辑node是NULL

link freeList;	// 空闲链表头链接, 被所有函数共享
void initNode(int n)
{
	freeList = (link)malloc(sizeof(*freeList) * (n + 1));	// 多分配一个给哑节点
	for (int i = 0; i < n; i++)
	{
		freeList[i].item = -1;
		freeList[i].next = &freeList[i+1];
	}
	freeList[n].item = -1;
	freeList[n].next = NULL;
}

	// 获取一个node:
	//		. 从空闲链表哑节点后边拿出一个

link newNode(Item item)
{
	link CN = deleteNext(freeList);

	CN->item		= item;
	CN->next		= NULL;
	return CN;
}

	// freeNode:
	//		. 将一个node回收到空闲链表中
	//		. 放入的位置为哑节点后边

void freeNode(link CN)
{
	link NN = freeList->next;
	freeList->next = CN;
	CN->next = NN;
}

	// insertNext:
	//		. 为参数1的node后边添加一个参数2node
void insertNode(link CN, link NN)
{
	NN->next = CN->next;
	CN->next = NN;
}

link deleteNext(link CN)
{
	link NN = CN->next;
	CN->next = NN->next;
	return NN;
}