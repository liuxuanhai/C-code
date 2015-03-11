// 程序清单 17.5
#include <stdio.h>
#include <stdlib.h>
#include "p495 接口_列表.cpp"

static void CopyToNode(Item item, Node * pnode);

void InitializeList(List * plist)
{
	*plist = NULL;
}

bool ListIsEmpty(const List * plist)
{
	return *plist == NULL ? true : false;
}

bool ListIsFull(const List * plist)
{
	bool full;
	Node * temp;
	if ((temp = (Node *)malloc(sizeof(Node))) == NULL)
		full = true;
	else
		full = false;
	free(temp);
	return full;
}

unsigned int ListItemCount(const List * plist)
{
	Node * current = *plist;
	unsigned int ct = 0;
	while (current != NULL)
	{
		ct++;
		current = current->next;
	}
	return ct;
}

bool AddItem(Item item, List * plist)
{
	Node * temp, * current;
	current = (Node *)malloc(sizeof(Node));
	if (current == NULL)
		return false;
	current->next = NULL;
	CopyToNode(item, current);
	if (*plist == NULL)
		*plist = current;
	else
	{
		temp = *plist;
		while (temp->next != NULL)
			temp = temp->next;  // temp++ 是个可笑的错误呀
		temp->next = current;
	}
	return true;
}

void Traverse(const List * plist, void (*pfun)(Item item))
{
	Node * temp = *plist;
	while (temp != NULL)
	{
		pfun(temp->item);
		temp = temp->next;
	}
}

void EmptyTheList(List * plist)
{
	Node * temp = *plist;
	*plist = NULL;
	Node * temp2;
	while (temp != NULL)
	{
		temp2 = temp->next;
		free(temp);
		temp = temp2;
	}
}

static void CopyToNode(Item item, Node * pnode)
{
	pnode->item = item;
}