// 程序清单 16.1 简单地预处理器的例子
#include <stdio.h>
#define TWO 2  
#define OW "Consistency is the last refuge of the unimagina\
tive. -Oscar Wilde" // 反斜线把这个定义延续到下一行
#define FOUR TWO*TWO
#define PX printf ("X is %d.\n", x)// PX 为类对象宏 他们用来代表值 他们的中间不能有空格
#define FMT "x is %d.\n" // 大部分编译器把主体当做语言符号类型字符串而不是字符型字符串. 空格当做语言符号的间隔而不是有几个空格当做几个字符

int main (void)
{
	int x = TWO;
	const char * fmt = "x is %d.\n"; // 也可以用字符常量的这种定义方式

	PX;
	x = FOUR;
	printf (FMT, x);
	printf ("%s\n", OW);
	printf ("TWO: OW\n");
	printf (fmt, x);

	return 0;
}
