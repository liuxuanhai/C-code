// 此为复习题 10.9 (5) 为编程练习1提供的头文件
#include <cstring>
class BankAccount
{
private:
	char name[40];
	char acctnum[25];
	double balance;
public:
	BankAccount(const char * client = "no name", const char * num = "no num", double bal = 0.0);  // 定义的时候就不用加上默认参数了
	void show(void) const;
	void deposit(double cash);
	void withdraw(double cash);
};