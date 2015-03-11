// p333 程序清单 12.5 (一)
#include <stdio.h>

void report_count ();
void accumulate (int k);

int count = 0;        // 文件作用域, 外部链接 静态变量, 未初始化的话自动给0

int main (void)
{
	int value;        // 自动变量, 未初始化的话值是随机的
	register int i;   // 寄存器变量, 不能取其地址

	puts ("输入一个正整数(0退出).");
	while (1 == scanf ("%d", &value) && value > 0)
	{
		++count;     // 使用文件作用域变量
		for (i = value; i >= 0; i--)
			accumulate (i);
	}
	report_count ();

	return 0;
}

void report_count ()
{
	printf ("一共进行了%d个循环周期!\n", count);
}