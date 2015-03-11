// 程序清单 4.17
// *使函数跳过相应的输入项目
#include <stdio.h>
int main(void)
{
	int i;
	scanf ("%*d %*s %d", &i);
	printf ("%d\n", i);

	return 0;
}