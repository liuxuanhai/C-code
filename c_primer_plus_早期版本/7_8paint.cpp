//条件运算符 ? :    //降级类型转换的转换规则
//c primer plus 程序清单 7.8
//paint.c -- 使用条件运算符 paint:涂料
#include <stdio.h>
#define COVERARE 200
int main (void)
{
	int sq_feet;
	int cans;

	printf ("Enter number of square feet to be painted: \n");
	while (scanf ("%d", &sq_feet) == 1)
	{
		cans = sq_feet / COVERARE;  //通过 '趋零截尾'  进行降级转换
		cans += ((sq_feet % COVERARE == 0) ? 0: 1);   // 条件运算符
		printf ("You need %d %s of paint.\n", cans, cans == 1 ? "can": "cans");  // 条件运算符选择输出输出字符串
		printf ("Enter next value (q to qiut): \n");
	}
	return 0;
}