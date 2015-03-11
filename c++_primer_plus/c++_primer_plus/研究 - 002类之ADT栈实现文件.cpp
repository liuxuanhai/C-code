#include "研究 - 002类之ADT栈.h"

Stack::Stack()
{
	top = 0;	// 指向栈顶的空位置
}

bool Stack::isEmpty() const
{
	return top == 0;
}

bool Stack::isFull() const
{
	return top == MAX;
}

bool Stack::push(const Item & item)
{
	if (top < MAX)
		items[top++] = item;
	else
		return false;
	return true;
}

bool Stack::pop(Item & item)
{
	if (top > 0)
		item = items[--top];
	else
		return false;
	return false;
}