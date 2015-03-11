// 分别输入he shixiong 和 he xiong 进行测试
#include <stdio.h>
#include <string.h>
int main(void)
{
	char name[40];
	char ch, c;

	scanf ("%s s%c", name, &ch);
	scanf ("%c", &c);
	printf ("\n%s----%c---%c---\n", name, ch, c);
	
	return 0;
}