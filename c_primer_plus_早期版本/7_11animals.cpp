// switch语句的使用
// c primer plus 程序清单 7.11
// animals.c -- 使用switch语句
#include <stdio.h>
#include <ctype.h>
int main (void)
{
	char ch;
	printf ("Give me a letter(字母) of alphabet, and I will give ");
	printf ("an animal name\nbeginning with that letter.\n");
	printf ("Please type in a letter: type # to end my act.\n");
	while ((ch = getchar()) != '#')  // 关系运算符!=的优先级大于赋值运算符= 所以如果没给ch = getchar()加上括号的话结果是ch=1
	{ 
		if ('\n' == ch)   // 加上这个以后如果在输入界面直接打回车不会显示I recognize only lowercase letters.
			continue;
		if (islower(ch))  // 只识别小写字母
			switch (ch)
			{
				case 'a':
					printf ("argali, a wild sheep of Asia.\n");
					break;
				case 'b':
					printf ("babirusa, a wild pig of Malay.\n");
					break;
				case 'c':
					printf ("coati, racoonlike mammal.\n");
					break;
				default:
					printf ("That's a stumper(难题)!\n");
			}                // switch语句结束
		else
			printf ("I recognize only lowercase letters.\n");
	//	while (getchar () != '\n')  
	//		continue;        // 跳过输入行的剩余部分
		while (getchar () != '\n') // 如果输入abc那么上个循环读取a 这个循环读取bc 并屏蔽他们
			;                // 说明continue在这只是个占位符
		printf ("Please type another letter or a #.\n");
	}                        // while循环结束
	printf ("Bye!\n");
	return 0;                
}