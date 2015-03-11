// 传引用
                       // 传引用与传指针的区别: 传引用的时候形参相当于给实参命了另一个名字,形参就是实参,相当于没有给形参新建一个变量,分配一个内存
                       //                       传指针的时候形参是实参的地址,形参新建了一个变量用来存放实参的地址
// 例5-3 用自定义函数实现两个整数的交换
#include <stdio.h>
void swap (int &, int &);      // 声明时候加上& 说明变量为一个引用变量
// void swap (int *, int *);   // 声明时加上了* 说明变量为一个指针
int main (void)
{
	int x = 10;
	int y = 20;
	
	printf ("变之前x = %d, y = %d\n", x, y);
	swap (x, y);               // 这里实际上是把x赋给了swap中的a
	printf ("变之后x = %d, y = %d\n", x, y);

	return 0;
}

void swap (int & a, int & b)
{
	int temp;
	
	temp = a;
	a = b;
	b = temp;
}