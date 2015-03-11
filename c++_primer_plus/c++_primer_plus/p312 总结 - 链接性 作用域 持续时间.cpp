// 全局变量分为引用声明和定义声明:
// extern int a; 这个是引用声明, 不会导致分配内存;
// extern int a = 1; 和 int a = 1; 这个是定义声明, 导致了内存的分配;

// const 对链接性的影响
// const 会把外部链接的全局变量转换成内部链接, 这样, 在头文件中包含const常量将不会导致重定义;
// extern const int a = 1; 都将改变这种默认属性将const常量声明为外部链接

// static 对于函数
// 可以使用static将函数声明为静态的(函数原型和定义中都必须加上)
// 这样, 函数就能隐藏外部链接的函数定义, 然后避免重定义;

#include <iostream>
using namespace std;

	// 由于9.6中已经声明了具有外部连接的int i所以这里直接声明int i将会被认为是二次定义, 但是声明为具有内部链接的全局变量是可以的, 并且会隐藏具有外部链接的同名变量
static int i;  // static关键字重载, 连接性为内部
	
	// 连接性为外部
double warming = 0.3;

void update(double);
void local	(void);

int main(void)
{

		// 初始化问题

			// 只要在变量初始化的时候等号右边的变量值已经初始化, c++就允许
	int a = 3;
	int b = a;
	int c = a + 4;

			// 然而这里不允许数组中放置变量是因为在分配内存阶段变量中的值是未初始化的, 所以这里将会不知道为数组分配多少内存
	//int ar[c]; 

	cout << b << endl;
	cout << c << endl;

	cout << "全局变量 warming 是 " << warming << endl;
	update(0.1);
	cout << "全局变量 warming 是 " << warming << endl;
	local();
	cout << "全局变量 warming 是 " << warming << endl;

	return 0;
}