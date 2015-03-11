// 编程练习 10.10 (8) 实现文件
#include "p378编程练习8_标准答案.h"

Simplist::Simplist(void)
{
	count = 0;
}

bool Simplist::isempty(void)
{
	return count == 0;
}

bool Simplist::isfull(void)
{
	return count == MAXLIST;
}

int Simplist::itemcount()
{
	return count;
}

bool Simplist::additem(Item item)
{
	if (count == MAXLIST)
		return false;
	else
		items[count++] = item;
	return true;
}

void Simplist::transverse(void (*pfun)(Item item))
{
	for (int i = 0; i < count; i++)
		(*pfun)(items[i]);
}