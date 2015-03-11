// 编程练习 11.13 (14)
// 自己制作的atoi();函数
#include <stdio.h>
#include <ctype.h>
#include <math.h>
int AtoI(char *);
int main(void)
{
	char ar[21];
	while (gets(ar))
		printf("%s -> %d\n", ar, AtoI(ar));

	return 0;
}
int AtoI(char * s)
{
	int i = 0, j = 0;
	int num = (int)'0' - '\0';
	int r = 0;
	char temp[21];
	while (s[i])
		if (isdigit(s[i]))
			temp[j++] = s[i++];
		else
			i++;
	temp[j] = '\0';
	for (int k = 0; k < j; k++)
		r += (int)(temp[k] - num) * (int)pow(10, double(j - k - 1));
	return r;
}