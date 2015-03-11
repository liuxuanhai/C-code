#include <stdio.h>
#include <time.h>
#include <stdlib.h>
typedef struct node *link;
typedef int			item;
struct node
{
	item Item;
	link next;
};

	// 倒置链表
link reverse(link);	// 返回尾node的指针

int main(void)
{
	struct node headin, headout;	// headin, 输入链表哑节点, 包含未排序数据, headout, 输出链表哑节点, 包含排序数据;
	int i;
	int N;	// 要排序的数据项个数

		// 输入项目个数

	printf_s("输入项目个数: ");
	scanf_s("%d", &N);

		// 产生随机值, 保存在headin链中

	link currentin = &headin;	// "当前"操作节点为输入表哑节点
	srand((unsigned long)time(0));
	for (i = 0; i < N; i++)
	{
		currentin->next = (link)malloc(sizeof(node));

			// "当前"操作节点为新节点
		currentin = currentin->next;
		currentin->next = NULL;
		currentin->Item = rand() % 1000;
	}

		// 输出headin链的数据

	currentin = headin.next;	// "当前"为输入哑节点后边的一个项
	for (i = 0; i < N; i++)
	{
		printf ("%d ", currentin->Item);
		currentin = currentin->next;
	}

		// 将headin链的node一个一个的插入到headout链中

	link nextin;
	link currentout;
	headout.next = NULL;
	for (currentin = headin.next, headin.next = NULL; currentin != NULL; currentin = nextin)	// 一直循环到输入链没有数据节点
	{
		nextin = currentin->next;

			// 寻找headout中合适的插入位置
		for (currentout = &headout; currentout->next != NULL; currentout = currentout->next)
			if (currentout->next->Item > currentin->Item)
				break;

			// 进行插入
		currentin->next = currentout->next;
		currentout->next = currentin;
	}

		// 输出headout链

	printf("\n\n\n\n");
	currentout = headout.next;
	for (i = 0; i < N; i++)
	{
		printf ("%d ", currentout->Item);
		currentout = currentout->next;
	}

		// 倒置链表

	printf("\n\n\n\n");
	currentout = reverse(&headout);;
	for (i = 0; i < N; i++)
	{
		printf ("%d ", currentout->Item);
		currentout = currentout->next;
	}

	return 0;
}

link reverse(link li)
{
	link Current, Next, Prev;
	
	Prev		= NULL;
	Current		= li;

	while (Current != NULL)
	{
			// 生成"下一个"节点
		Next = Current->next;	// 没有在上面初始化Next是考虑到Current下面没有node的情况, 在这里初始化表明, 只有在Current != NULL的情况下才有Next的存在;

			// 链接倒置
		Current->next = Prev;
		
			// 刷新"上一个"和"当前"节点
		Prev	= Current;
		Current	= Next;
	}

	return Prev;
}