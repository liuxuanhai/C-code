// 关于检测文件结尾不同的操作系统有多种检测方式(用ctrl+z/d标记结尾或存储文件大小信息)
// 不管操作系统检测文件结尾的方法是什么, 都会令getchar()和scanf()的返回值为EOF
// 程序清单 8.2
#include <stdio.h> // 定义了EOF
int main(void)
{
	int ch; // char的范围可以为0-255但是EOF的值有可能为-1
			// 但是getchar()的类型是int所以他可以读取EOF
			// 在使用有符号char类型的实现中, 将ch声明为char类型仍然是可以的. 但是不是最好的

	while(EOF != (ch = getchar())) // 这里只有键入ctrl+z才能退出
		putchar(ch);

	return 0;
}