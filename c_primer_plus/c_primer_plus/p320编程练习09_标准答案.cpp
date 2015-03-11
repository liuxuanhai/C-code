// 编程练习 11.13 (9) 标准答案
#include <stdio.h>
#define LEN 81
int drop_space(char *);
int main(void)
{
	char orig[LEN];

	while (gets(orig) && orig[0] != '\0')
	{
		printf("一共删除了%d个空格\n", drop_space(orig));
		puts(orig);
	}
	puts("Bye!");

	return 0;
}
int drop_space(char * s)
{
	int ct = 0;
	char * pos;
	while (*s)
	{
		if (*s == ' ')
		{
			ct++;
			pos = s;
			do
			{
				*pos = *(pos + 1);
				pos++;
			}while (*pos);
		}
		else
			s++;
	}
	return ct;
}