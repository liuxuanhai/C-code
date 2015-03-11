// scanf()读取失败后悔一直尝试读取还是会直接返回错误数值
// 未被读取的值会不会被用作下次读取?   是的
// scanf()读取不进去会返回0然后不再执行本句scanf()只有遇到硬件错误或者到了文件结尾才回返回EOF(-1)
#include <stdio.h>
int main(void)
{
	int in;
	char ch;

	printf("EOF = %d\n", EOF);
	printf("%d\n", scanf("%d", &in));
	scanf("%c", &ch);
	printf("%c\n", ch);
	

	return 0;
}