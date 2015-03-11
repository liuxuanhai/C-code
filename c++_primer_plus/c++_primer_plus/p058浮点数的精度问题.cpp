// 程序清单 3.9
#include <iostream>
int main()
{
	using namespace std;

	float a = 2.34E+22f;
	float b = a + 1.0f;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "b - a = " << b - a << endl;
	// 按理说b - a应该为1然而事实上结果为0, 问题在于, 
	// 2.34E+22是一个小数点左边有23位的数字, 加上1, 
	// 就是在第二十三位加上一. 单float类型只能表示数
	// 字中的前六位或者前七位, 因此修改第二十三位对这个值不会有任何影响

	return 0;
}