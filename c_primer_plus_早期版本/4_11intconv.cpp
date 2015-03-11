//转换说明符 -- 不匹配的转换说明符
//c primer plus 程序清单 4.11
//intconv.c  --  一些不匹配的整数转换
#include <stdio.h>
#define PAGES 336
#define WORDS 65618
int main ()
{
	short num = PAGES;
	short mnum = -PAGES;
	
	printf ("num as short and unsigned short: %hd %hu\n",num,num);
	printf ("-num as short and unsigned short: %hd %hu\n",mnum,mnum);
	printf ("num as int and char: %d %c\n",num,num);
	printf ("WORDS as int,short,and char: %d %hd %c\n",WORDS,WORDS,WORDS);
	return 0;
}