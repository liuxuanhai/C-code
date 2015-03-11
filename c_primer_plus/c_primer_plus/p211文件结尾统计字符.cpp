// 编程练习 1
// 设计一个程序, 统计从输入到文件结尾为止的字符数
#include <stdio.h>
int main(void)
{
	int num_char = 0;

	while(EOF != getchar()) // 注意: 只有新行第一个字符为ctrl+z才能有效返回EOF
		num_char++;
	printf("此次输入一共包含%d个字符.", num_char);

	return 0;
}