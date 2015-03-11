// p293 程序清单 11.8
#include <stdio.h>
#define DEF "I am a #defined string."

int main (void)
{
	
	char str[80] = "An array was initialized to me!";
	char s[] = {'w', 'o', 'w'};
	char * str2 = "A pointer was initialized to me!";

	puts ("I am an argument of puts()!");  // argument 参数
	printf("...%d...", puts (DEF));                            // puts 函数在输出时会自动加上换行符
	puts (str);
	puts (str2);
	puts (&str[5]);
	puts (str2 + 4);
	puts (s);                              // 找不到正确的'\0'!!!

	return 0;
}