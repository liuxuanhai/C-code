#include <iostream>
#include "研究 - 003类之Time类.h"

int main()
{
	using	std::cout;
	using	std::cin;
	Time	planning(9);
	Time	coding(2, 22);
	Time	fixing(5, 55);
	Time	total;

	cout << "计划时间 = ";
	planning.Show();

	cout << "编程时间 = ";
	coding.Show();

	cout << "准备时间 = ";
	fixing.Show();

	//total = coding.Sum(fixing);
	//total = coding.operator+(fixing);
		
		// 使用 '+' 运算符代替上边两种写法
	total = planning.operator+(coding + fixing);	// '+' 左边是调用对象, 右边是参数传递对象
	cout << "总共时间 = ";
	total.Show();

		// 使用 '*' 实现 对象 * double
	cout << "编程时间 * 2.2 = ";
	(coding * 2.2).Show();	// 这里有个问题, 只能使用 coding * 2.2 而不能使用 2.2 * coding, 所以要借助友元函数实现

		// 友元实现 double * 对象
	cout << "3.3 * 编程时间 = ";
		(3.3 * coding).Show();

		// 友元实现 "<<"
	cout << total;

	return 0;
}