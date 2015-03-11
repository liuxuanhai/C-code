// 程序清单 9.6
#include <iostream>
extern double warming; // use waiming from another file
int i;
// function prototypes
//void update(double);
//void local();
	// 这里二次声明原型不算错, 但是不声明也不影响

using std::cout;
void update(double dt) // modifies global varible
{
	extern double warming;  // optional redeclaration
		// 这里算是对外部变量的二次引用 这次引用只对本代码块可见 但是更改的值可以影响外部变量warming
	warming += dt;         // uses gloabal warming
	cout << "Updating global warming to " << warming;
	cout << " degrees.\n";
}

void local()
{
	double warming = 0.8;  // new varible hides extern one
	cout << "Local warming = " << warming << " degrees.\n";
	// Access global varible with the scope resolution operator
	cout << "But global warming = " << ::warming << "degrees.\n";
								// :: 作用域解析运算符 它使得被隐藏的warming得以被访问
}