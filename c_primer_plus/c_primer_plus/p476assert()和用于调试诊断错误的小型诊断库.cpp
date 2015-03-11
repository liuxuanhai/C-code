// 程序清单 16.16
#include <stdio.h>
//#define NDEBUG      // 调试成功以后在assert.h前面写上这个系统会忽略所有assert()
#include <assert.h> // assert 维护 诊断错误的小型库
#include <math.h>
#include <stdlib.h>

int main (void)
{
	double x, y, z;
	puts ("Enter a pair of numbers (0 0 to quit):");
	while (2 == scanf ("%lf %lf", &x, &y) && (x != 0 || y != 0))
	{
		z = x * x - y * y; // 应该是＋错写成了-
		assert (z >= 0);  // 标示出程序中某个条件应为真的关键位置, 并在条件为假时用assert()语句终止该程序
		/*if (z < 0)
		{
			puts ("z less than 0");
			abort ();
		}*/
		printf ("Answer is %f\n", sqrt(z));
		puts ("Next pair of numbers:");
	}
	puts ("done!");

	return 0;
}