// 演示程序
#include <stdio.h>
int main(void)
{
	double dou = 8;
	char ch;
	int in;

	//printf("\\%d\\\n", scanf("%f", &dou));
	//printf("%lf\n", dou);
	// 传递的是dou的地址, 所以不存在做参数的隐式的类型转换
	// 类型不匹配,scanf()还是返回了1, 说明读入了并且储存了

	printf("\\%d\\\n", scanf("%d", &in));
	printf("%d\n", in);
	// 输入字母后scanf()返回的值是0

	//scanf("%lf", &dou);
	//printf("%lf", dou);

	return 0;
}