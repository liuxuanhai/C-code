// 编程练习 10.10 实现文件
#include <iostream>
#include "p377编程练习1.h"

BankAccount::BankAccount(const char * client, const char * num, double bal)  // 在原型中写上默认参数就可以了, 定义中不用写
{
	strncpy(name, client, 39);
	name[39] = '\0';
	strncpy(acctnum, num, 24);
	acctnum[24] = '\0';
	balance = bal;
}

void BankAccount::show(void) const
{
	std::cout << "Name: " << name << std::endl
		<< "Acctnum: " << acctnum << std::endl
		<< "Balance: " << balance << std::endl;
}

void BankAccount::deposit(double cash)
{
	balance -= cash;
}

void BankAccount::withdraw(double cash)
{
	balance += cash;
}