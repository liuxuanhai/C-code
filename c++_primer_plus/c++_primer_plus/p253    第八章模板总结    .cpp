// 自己总结
// 1. 函数模板的具体化(显示实例化, 隐式实例化, 显示具体化)
// 2. 函数模板的重载
// 3. decltype
// 4. 后置类型声明

#include <iostream>
using namespace std;

template<typename T>
void Swap(T a, T b)  // 未能实现交换, Swap<int &>(a, b);  // 报错,  T temp 转化成int & temp的话没有初始化;
{
	T temp;
	temp = a;
	a = b;
	b = temp;
}
template <typename T>
void Swap2(T & a, T & b)
{
	T temp;
	temp = a; 
	a = b; 
	b = temp;
}
template<typename T>
void Swap3(T * a, T * b)
{
	T temp;
	temp = *a; 
	*a = *b; 
	*b = temp;
}
template void Swap2<char>(char &, char &);  // 显示实例化

template<class T1, class T2>
auto xy(T1 x, T2 y) -> decltype(x + y)
{
	decltype(x + y) result = x + y;
	return result;
}

int main(void)
{
	
	int a = 0;
	int b = 1;
	cout << a << b << endl;
	Swap(a, b);  // 隐式实例化
	cout << a << b << endl;
	//Swap<int &>(a, b);  // 报错,  T temp 转化成int & temp的话没有初始化;
	//cout << a << b << endl;
	Swap2(a, b);
	cout << a << b << endl;

	char aa = 'a';
	char bb = 'b';
	cout  << aa << bb << endl;
	Swap2(aa, bb);  // 使用显示实例化
	cout  << aa << bb << endl;

	int aaa = 000;
	double bbb = 111;
	cout << aaa << bbb << endl;
	Swap<double>(aaa, bbb);
	//Swap2<double>(aaa, bbb);  // 显示实例化方法2不能实现double & 类型指向强制类型转换int类型aaa为double的aaa;
	cout << aaa << bbb << endl;
	// Swap2((double &)aaa, bbb); // 程序崩溃
	// cout << aaa << bbb << endl;

	//Swap3<double>(&aaa, &bbb);  // 显示实例化方法2不能实现double * 类型指向强制类型转换int类型aaa为double的aaa;
	//Swap3((double *)&aaa, &bbb);
	//cout << aaa << bbb << endl;  // 程序崩溃

	int x = 2;
	double y = 3.023;
	cout << xy(x, y) << endl;

	return 0;
}