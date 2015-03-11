#include "05dxList.h"
#include <stdlib.h>

List::List()
{
	ItemIni(nilNode.item);
	nilNode.next = &nilNode;
	length	= 0;
	linkTail = &nilNode;
}

void List::Travel(void (*fun)(link))
{
	for (List::link x = GetHead(); x != GetSentinel(); x = x->next)
		fun(x);
}

List::link List::Search(Item item)	// Search返回的是目标节点前一个节点的链接
{
	for (List::link x = GetSentinel(); x->next != GetSentinel(); x = x->next)
		if (ItemIsEqual(x->next->item, item))
			return x;
	return nullptr;
}

// 所有添加node的函数都会引用这个函数将数据添加进去
void List::AddNext(link li, link li1)
{
	if (li == linkTail)	// 如果要在尾节点后边插入新节点, 那么尾节点链接应该指向新节点
		linkTail = li1;
	li1->next	= li->next;
	li->next	= li1;
	length++;
}

void List::AddNext(link li, Item item)
{
	link t = (link)malloc(sizeof *t);
	ItemAssign(t->item, item);
	t->next = nullptr;
	AddNext(li, t);
}

void List::AddHead(link newLi)
{
	AddNext(GetSentinel(), newLi);
}

void List::AddHead(Item newItem)
{
	AddNext(GetSentinel(), newItem);
}

void List::AddTail(link li)
{
	AddNext(GetTail(), li);
}

void List::AddTail(Item item)
{
	AddNext(GetTail(), item);
}

bool List::RemoveNext(link li, link & t)
{
	if (GetSentinel() == li->next || !li)	// 如果是尾节点或者空链接, 不能再删除下一个了
		return false;
	t = li->next;
	li->next = li->next->next;
	length--;
	if (li->next == GetSentinel())			// 如果移除了尾节点, 更新linkTail
		linkTail = li;
	return true;
}

bool List::DelNext(link li)
{
	link t;
	if (!RemoveNext(li, t))
		return false;
	delete t;
	return true;
}

bool List::RemoveItem(Item item, link & t)
{
	link li;
	if (!(li = Search(item)))	// 如果没有找到(nullptr), 则直接返回false 注意: Search返回的是目标节点前一个节点的链接
		return false;
	RemoveNext(li, t);
	return true;
}

bool List::DelItem(Item item)
{
	link li;
	if (!(li = Search(item)))	// 如果没有找到(nullptr), 则直接返回false 注意: Search返回的是目标节点前一个节点的链接
		return false;
	DelNext(li);
	return true;
}

bool List::RemoveHead(link & t)
{
	if (GetSentinel()->next == GetSentinel())	// 如果只有哨兵节点, 则移除失败
		return false;
	RemoveNext(GetSentinel(), t);
	return true;
}

bool List::DelHead()
{
	if (GetSentinel()->next == GetSentinel())	// 如果只有哨兵节点, 则删除失败
		return false;
	DelNext(GetSentinel());
	return true;
}

bool List::RemoveTail(link & t)
{
	if (GetSentinel()->next == GetSentinel())	// 如果只有哨兵节点, 则移除失败
		return false;
	RemoveNext(Search(linkTail->item), t);
	return true;
}

bool List::DelTail()
{
	if (GetSentinel()->next == GetSentinel())	// 如果只有哨兵节点, 则删除失败
		return false;
	DelNext(Search(linkTail->item));
	return true;
}

List::~List()
{
	for (List::link x = GetHead(); x != GetSentinel(); x = GetHead())
		DelHead();
}

void List::SetItem(link li, Item item)
{
	ItemAssign(li->item, item);
}