#include <iostream>
#include <cstdlib>
#include <ctime>
#include "015对可改变大小的栈模板的实现方法的探究_头文件.h"
int main()
{
	int temp = -1;
	Stack<int> a(8);
	a.push(1);
	a.push(2);
	a.push(3);
	a.push(4);
	a.push(5);
	a.push(6);
	
	a.pop(temp);
	std::cout << temp << "被删除\n";
	/*a.pop(temp);
	cout << temp << "被删除\n";
	a.pop(temp);
	cout << temp << "被删除\n";
	a.pop(temp);
	cout << temp << "被删除\n";
	a.pop(temp);
	cout << temp << "被删除\n";
	a.pop(temp);
	cout << temp << "被删除\n";
	a.pop(temp);*/
	return 0;
}