// p291 程序清单 11.6
// 注意到gets();有个弊端, 他不能检查读入是否超过数组("蠕虫"病毒的由来). fgets();增加了这项功能
// 如果第二个参数是n则他可以读入n-1个字符或者读完一个换行符为止, 他会储存换行符而不是像gets()那样把他丢弃
// 他需要第三个参数来指明读哪一个文件
// ##### 除了以上三点, 其他的fgets()与gets()一样 #############
#include <stdio.h>
#define MAX 81

int main (void)
{
	char name[MAX];
	char name1[4];
	char * namePtr;

	printf ("告诉我你的名字:");			// fgets 会把换行符也给读进去
	namePtr = fgets (name, MAX, stdin);   // 为字符串分配的地址name, 长度MAX, 输入的方式stdin(standard input 键盘输入)
	printf ("%s? Hello, %s\n", name, namePtr);
	printf("我最多只能保存三个输入字符:");
	fgets(name1, 4, stdin);
	printf("%s\n", name1);

	printf("一次循环吃三个字符(EOF可以结束):\n");
	while (fgets(name1, 4, stdin) != NULL)
	{
		printf("%s\n", name1);
		printf("一次循环吃三个字符(EOF可以结束):\n");
	}
	return 0;
}