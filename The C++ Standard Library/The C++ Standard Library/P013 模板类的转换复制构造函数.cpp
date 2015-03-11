#include  <iostream>
using namespace std;
template <class T>
class MyClass
{
public:
	// copy constructor with implicit type conversion
	// - dose not hide implicit copy constructor
	// 隐式类型转换复制构造函数
	// - 不隐藏隐式复制构造函数
	template <class U>
	MyClass(const MyClass<U> & x){}
	MyClass(){}

	// 基本型别的显示初始化
	// 采用不含参数的, 明确的constructor调用语法 int i = int(); 基本型别会被初始化为0
	void f() { T x = T(); }		// T x = T(); 这个特性保证在template程序代码中, 任何型别有一个确切的初始值;
};

int main()
{
	MyClass<double> xd;
	MyClass<double> xd2(xd);	// 调用 built-in 复制构造函数
		// 这里xd2和xd型别完全一致, 所以他被内建的复制构造函数初始化

	MyClass<int> xi(xd);		// 调用模板构造函数
		// xi和xd的型别不同, 所以他使用template构造函数进行初始化
}