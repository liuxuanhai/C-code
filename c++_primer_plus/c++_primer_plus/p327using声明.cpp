#include <iostream>
using namespace std; // using 编译指令使得std名称空间的所有名称全局可用
#include "p326名称空间.cpp"

// 在函数外面使用using声明时, 将把名称添加到全局名称空间中
using Jack::pail; // put pail into global namespace

void other();
char fetch; // global fetch
int main()
{
	cin >> pail; // read a value into Jack::fetch
	other();

// using声明将特定的名称添加到他所属的声明区域中, 例如main()中的using声明Jill::fetch将fetch添加到main()定义的声明区域中
	using Jill::fetch;   // a using declaration
		// put fetch into local namesapce 这里把全局变量fetch覆盖了
// using声明在同名局部变量之前使用
	//double fetch = 1.0; // Error! Already have a local fetch // error C2086: “double Jill::fetch”: 重定义
	cin >> fetch;		   // read a value into Jill::fetch
	cout << fetch << endl;
	cin >> ::fetch;	   // read a value into global fetch
	cout << ::fetch << endl;
// using声明在局部变量之后声明									// 上面的导致的是重新定义下面的是多次声明时不一样的, 而且都是后声明的那行出错, 一个重定义一个多次声明是因为有个声明的时候初始化了
															// 但是两个不同的名称空间的相同名称再次using声明的时候会覆盖上一声明
	//int pp = 11;
	using Jill::pp;      //  error C2874: using 声明导致“Jill::pp”的多次声明
	cout << "名称空间初始化的pp = " << pp << endl;

	return 0;
}

void other()
{
	cout << pail << endl;
}