// 编程练习 10.10 (5) 实现文件
#include <iostream>
#include "p378编程练习5.h"

Stack::Stack()
{
	for (int i = 0; i < SIZE; i++)
	{
		stack[i].fullname[0] = '\0';
		stack[i].payment = 0.0;	
	}
	tot_payment = 0.0;
	num = 0;
}

void Stack::show() const
{
	std::cout << "\nTot_payment: " << tot_payment << std::endl;
	for (int i = 0; i < num; i++)
		std::cout << "Name: " << stack[i].fullname
			 << "    Payment: " << stack[i].payment 
			 << std::endl;
}

bool Stack::add(const Item & stack_)
{
	if (num < SIZE)
	{
	stack[num++] = stack_;
	tot_payment += stack_.payment;
	}
	else
	{
		std::cout << "无法加入, 栈已满." << std::endl;
		return false;
	}
	return true;
}

bool Stack::de()
{
	if (num > 0)
		num--;
	else
	{
		std::cout << "栈已经空了.\n";
		return false;
	}
	return true;
}