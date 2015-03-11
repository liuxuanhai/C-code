// 程序清单 9.1
// .函数原型		.使用#define或const定义的符号常量	.结构声明
// .类声明	     .模板函数	.内联函数
// 符号常量能够导致分配内存, 为什么可以在头文件中而不会引起二次定义呢? 原因是在所有函数外面的变量有可能是外部的连接, 但是const限定符下的常量全部都是内部链接常量, 所以const常量对于每个文件都是私有的.  但是出于某种原因, 如果非要把他弄成外部链接的话, 可以使用extern覆盖掉其内部链接的特性, 但是在其他文件中使用他的时候必须加上extern,这与普通变量是不同的, 普通变量不用extern就可以声明其为外连接
// 内联函数也导致分配内存, 但是内联函数是函数的一个列外, 他可以被多次定义, 但是要求每个定义都必须相同
#ifndef DANDUBIANYI_H_ // 防止多次编译头文件
#define DANDUBIANYI_H_ 
struct polar
{
	double distance;
	double angle;
};

struct rect
{
	double x;
	double y;
};

polar rect_to_polar(rect xypos);
void show_polar(polar dapos);

#endif