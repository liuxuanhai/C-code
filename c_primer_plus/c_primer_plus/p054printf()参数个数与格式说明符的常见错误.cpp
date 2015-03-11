// 程序清单 3.9
// 关于pringf()的参数问题
#include <stdio.h>
int main (void)
{
	int Int = 4;
	int Int2 = 5;
	float Float = 5.0f;

	printf ("%d\n", Int, Int2); // 参数太少的时候无法显示多出来的参数
	printf ("%d %d\n", Int);    // 参数太少的时候没有对应的格式说明符为0(有的是垃圾值)
	printf ("%d %f", Float, Int);
								// 说明符与参数类型不符的情况下显示为0(有的是垃圾值)

	return 0;
}