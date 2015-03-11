// 编程练习 10.10 (8) 实现文件
#include "p378编程练习8.h"
#include <iostream>

List::List()
{
	top = 0;
}

bool List::add(Item n)
{
	if (top >= LEN)
		std::cout << "列表已经满了\n";
	else
	{
		list[top++] = n;
		return true;
	}
	return false;
}

bool List::isempty() const
{
	return top == 0;
}

bool List::isfull() const
{
	return top == LEN;
}

void List::visit(void (*pf)(Item &))
{
	if (top > 0)
		for (int i = 0; i < top; i++)
			(*pf)(list[i]);
	else
		std::cout << "列表是空的, 无法执行当前操作.\n";
}

void List::show() const
{
	if (isempty())
		std::cout << "列表是空的\n";
	else
		for (int i = 0; i < top; i++)
			std::cout << list[i] << std::endl;
}