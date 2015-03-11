// 程序清单 11.6
#include <iostream>
#include "p384运算符重载实现时间相加.h"

Time operator*(double d, const Time & t);  // 用非友元实现(int)*(class对象)的调用方式

int main()
{
	using std::cout;
	using std::endl;
	Time planning;
	Time coding(2, 40);
	Time fixing(5, 55);
	Time total;
	
	cout << "planning time = ";
	planning.show();
	cout << endl;

	cout << "coding time = ";
	coding.show();
	cout << endl;

	cout << "fixing time = ";
	fixing.show();
	cout << endl;

	total = coding + fixing;  // 直接使用重载运算符, 左边为调用对象, 右边为参数
	// operator notation
	cout << "coding + finxing = ";
	total.show();
	cout << endl;

	Time morefixing(3, 28);
	cout << "more fixing time = ";
	morefixing.show();
	cout << endl;
	total = morefixing.operator+(total);  // 运算符的函数调用
	// function notation
	cout << "morefixing.oprator+(total) = ";
	total.show();
	cout << endl;

	total = total * 2;
	total = 2 * total;
	cout << "total = total * 2 : ";
	cout << total;  // 利用友元函数实现重载"<<"实现输出时间
	cout << endl;

// t4 = t1 + t2 + t3;  =>>  t4 = t1.operator(t2 + t3);  =>>  t4 = t1.operator(t2.operator(t3));   // 因为返回值是一个Time对象, 所以能够实现
							// 因为 + 是从左向右结合的运算符, 所以首先分解成这样
	return 0;
}