// p290 程序清单 11.5 
// . 读入一行, 把'\n'替换成'\0'
// . 不会检查字符是否超出了数组范围, 很可能导致栈被破坏
#include <stdio.h>

int main (void)
{
	char name[5]; // 只能存入4个字符加上一个自动存储的'\0'
	char name2[888];
	char * namePtr;

	printf ("请输入你的名字:");
	namePtr = gets (name);  // 参数为地址,返回值为地址
		// gets()返回的和传递给他的是一个指针, 因为gets()从输入缓存中直接将字符串保存在传入地址开始的内存中, 所以输入字符串只有一个备份, 就是保存在传入地址的备份, 所以返回的指针即为数组地址, 即namePtr最后也指向name数组
		// gets()的返回值有两种, 一种是参数地址, 另一个是在读取到了文件结尾EOF的时候返回NULL(空指针)
		// 空指针(NULL)和空字符不一样('\0'), 空指针是一个地址, 空字符是一个char类型的数据对象, 其值为0, 数值上两个都可以用0表示, 但是他们的概念不同, NULL是一个空指针, 而0是一个char类型的常量
	printf ("%s? Hello, %s.\n", name, namePtr);

	printf("输入(EOF可以结束):");
	while (gets(name2) != NULL && name2[0] != '\0') // #######空行和EOF结束的表示方法###########
	{
		puts(name2);
		printf("输入(EOF可以结束):");
	}

	return 0;
}