#include <iostream>
using namespace std;

	// 引用上一个文件的warming
extern double warming;
// extern double warming = 0; 这个会导致多重定义
// double warming; 这个会导致多重定义
// static double warming = 50;  // 这个不会导致多重定义, 但是会隐藏外链接的全局变量warming

	// 定义一个全局变量
int i;

	// 在这里在声明函数原型一遍也是可以的
	// 这就好比是include了一个头文件, 里面的东西只是类型的声明, 不会导致内存的分配

void update(double);
void local();
void local();  // 即使在同一个文件中声明原型两次也没事, 反正不分配内存是吧
//int temp;     // 这里就不行了, 因为这里是不是重复声明, 而是重复定义, 为同一个名字分配两块空间当然不行了
//int temp;
extern double warming; // 多次引用声明warming是可以的, 反正不会导致内存的分配, 是吧
extern double warming;
void local(double);  // 这里只是声明了, 并没有给出定义, 当主函数中调用他的时候会报错

void update(double dt)
{
	extern double warming;  // 这个不加一样可以用, 这里加上只是表明本函数使用了其他文件的变量
	warming += dt;
	cout << "将全局变量warming更新为: " << warming << endl;
}

void local(void)
{
	double warming = 0.8;  // 这里将会隐藏全局变量warming
	cout << "局部变量warming是: " << warming << endl;

		// 使用被隐藏的变量的方法

	cout << "全局变量通过作用域解析符访问为: " << ::warming << endl;
}