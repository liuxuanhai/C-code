#include <iostream>
using namespace std;
void fun(const int &a)
{
	cout << a << endl;
}
void fun2(int &a)
{
	cout << a << endl;
}
int main(void)
{
	const int aa = 1;
	int & bb = aa;  // 不能为const常量创建非const引用
	const int & bbb = aa;
	const int & bbbb = 3; // 生成了临时变量 
	fun(3);  // 这里生成了一个临时变量, 引用a是临时变量的别名;
	fun2(2);  // 这里不能生成临时变量
	//	生成临时变量的规则:
	//		1. 引用参数是const
	//		2. 实参的类型正确, 但是不是左值;
	//		3. 实参类型不正确, 但是可以转换成正确类型;
	fun(aa);
	fun2(aa);  // 这里不能将不可修改的左值赋值给非const引用
}