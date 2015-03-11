// 程序清单 4.16
// *修饰符和printf()函数
// 使用了%*d后那么参数中应该一个指明*的值, 一个指明d的值
#include <stdio.h>
int main(void)
{
	printf ("--%*d---\n", 5, 3);
	printf ("--%*.*f---", 5, 2, 3.2);

	return 0;
}