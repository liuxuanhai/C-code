// p292 程序清单 11.7
// scanf();决定输入结束的方法有两种: . 以遇到的第一个非空白字符开始, 在下一个空白字符结束
//								 . 如果指定了字符的宽度(%5s), 以遇到的第一个非空白字符开始, 在读取了5个字符或遇到空白字符结束
// ###但是scanf();也不检查是否输入超过了数组的范围
// scanf的返回值有两种: . 成功读取的数目    . 遇到文件结束的时候返回一个EOF
#include <stdio.h>

int main (void)
{
	char name1[7];
	char name2[7];
	int count;
	
	
	printf ("告诉我两个名字:");  // 分别输入123和abc 1234和abc 123和abcdef
	count = scanf ("%3s %5s", name1, name2); // scanf 的返回值为成功读入数据的个数;
	printf ("你告诉了我%d个名字, %s和%s.\n", count, name1, name2);
	while (scanf("%s", name1) != EOF)  // 如果输入超过了留个字符的话结束后显示内存被破坏!!!!!!!!!
	{
		printf("%s, 不是EOF\n", name1);
	}
	/*while (0 == scanf("&s", name1))
		printf("返回值为0的情况\n");*/
	return 0;
}