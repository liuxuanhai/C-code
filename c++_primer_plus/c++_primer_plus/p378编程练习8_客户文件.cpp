// 编程练习 10.10 (8) 客户文件
#include "p378编程练习8.h"
#include <iostream>
using namespace std;
void chengshi (Item &);
int main()
{
	List lis;
	Item ite;

	lis.show();
	cout << "---\n";
	lis.add(111);
	cout << "---\n";
	lis.show();
	cout << "---\n";
	lis.add(222);
	lis.show();
	cout << "---\n";
	lis.visit(chengshi);
	lis.show();

	return 0;
}

void chengshi(Item & aa)
{
	aa *= 10;
}