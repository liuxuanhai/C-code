// 输入 -> 程序处理 -> 遇见'#' -> 报告'ei'出现的次数
// c primer plus 编程练习 p187 6
#include <stdio.h>
int main ()
{
	char ch;
	int num = 0;
	int flag = 0;  // 标志

	printf ("请输入一串字符,我将为你寻找一共多少个ei(#结束程序):\n");
	while ((ch = getchar()) != '#')
	{
		if ('e' == ch)
		{
			flag = 1;
			continue;                           // 避免无用判断
		}
		else if ('i' != ch)
		{
			flag = 0;                          // 避免系统判定eai也为一个ei 在e改变标志为1时a又改回去了为0
		}
		if ('i' == ch && 1 == flag)
		{
			num++;
			flag = 0;                          // 别忘了回0 
		}
		if ('\n' == ch)                        // 设置点回车输出一共多少个ei
		{
			printf ("一共有%d个ei.\n", num);
			num = 0;                            // 又忘了- -!
		}
	}
	return 0;
}