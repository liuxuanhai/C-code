// 使用指针在函数间通信
                       // 传引用与传指针的区别: 传引用的时候形参相当于给实参命了另一个名字,形参就是实参,相当于没有给形参新建一个变量,分配一个内存
                       // 传指针的时候形参是实参的地址,形参新建了一个变量用来存放实参的地址
// c primer plus 程序清单 9.15 p238
// swap3.c -- 使用指针完成交换
#include <stdio.h>
void interchange (int * u, int * v);  // 也可以这样声明:void interchange (int *, int *); ANSI原型可以省略变量名称

int main (void)
{
	int x = 5, y = 10;

	printf ("Originally x = %d and y = %d.\n", x, y);
	interchange (&x, &y);             // 向函数传递地址,即u = &x
	printf ("Now x = %d and y = %d.\n", x, y);

	return 0;
}

void interchange (int * u, int * v)
{
	int temp;

	temp = *u;                        // 不能够写成temp = u 
	*u = *v;
	*v = temp;
}