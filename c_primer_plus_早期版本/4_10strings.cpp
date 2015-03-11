//c primer plus 程序清单 4.10 使用修饰符和标志示例(4)
//strings.c -- 字符串的格式化
#include <stdio.h>
#define BLURB "Authentic imitation!"
int main ()
{
	printf ("/%2s/\n", BLURB);
	printf ("/%24s/\n", BLURB);
	printf ("/%24.5s/\n", BLURB);
	printf ("/%-24.5s/\n", BLURB);
	return 0;
}