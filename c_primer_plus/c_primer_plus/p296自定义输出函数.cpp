// p296 程序清单 11.12
#include <stdio.h>
void puts1 (const char *);       //一个等同于puts()的函数只是没有了自动加回车
int puts2 (const char *);        //一个等同于puts()的函数只是会返回字符串的个数(自动加的回车不计入算数)

int main (void)
{
	puts1 ("If I'd as much money");
	puts1 (" as I could spend. \n");
	printf ("I count %d characters.\n",
			puts2("I never would cry old chairs to mend.")); //  chairs 主席,教授,椅子
			// 在取puts2()的返回值的过程中c必须先执行puts2()所以puts2中的参数会先显示在屏幕上
	return 0;
}

void puts1 (const char * string)
{
	while (*string)             // 等同于*string != '\0'
		putchar (*string++);    // ++的优先级高于*所以是地址加1而不是地址指向的值加一

	return;
}

int puts2 (const char * string)
{
	int num = 0;

	while (*string != '\0')
	{
		putchar (*string++);
		num++;
	}
	putchar ('\n');

	return num;
}