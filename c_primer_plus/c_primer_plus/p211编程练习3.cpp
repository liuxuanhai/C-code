// 编程练习 3
// 统计std输入文件中的大写和小写字母个数
#include <stdio.h>
#include <ctype.h>
int main(void)
{
	int big = 0, little = 0;
	char ch;
	while(EOF != (ch = getchar()))
		if(isupper(ch))
			big++;
		else if(islower(ch))  // else与最近的一个if相连接, 所以这样即使while没有用花括号也是可以的
			little++;
	printf("大写字母有%d个, 小写字母有%d个\n",
		big, little);

	return 0;
}