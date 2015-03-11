// 关于可变函数参数的深入分析
#include <stdio.h>
#include <stdarg.h>

int printff(char *, ...);

int main(void)
{
	printff("I am %d years old, my name is %s.\n", 21, "heshixiong");

	return 0;
}

int printff(char * str, ...)
{
	int lim;
	int i;
	char biaoshi[100];
	char * dizhi[100];
	va_list ap;

	for (lim = 0, i = 0; str[i]; i++)
		if (str[i] == '%')
		{
			dizhi[lim] = &str[i];
			biaoshi[lim++] = str[i+1];
		}
	biaoshi[lim] = '\0';
	va_start(ap, lim);
	printf("....%d....", va_arg(ap, int));
	for (int j = 0; str[j]; j++)
		if (str[j] != '%')
			putchar(str[j]);
		else
		{
			j++;
			if (str[j] == 'd')
				printf("%d", va_arg(ap, int));
			else if (str[j] == 's')
				printf("%s", va_arg(ap, char *));
		}
}