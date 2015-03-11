//嵌套循环 -- 金字塔
#include <stdio.h>
int main (void)
{
	int i,i1,i2,i3,num;
	char ch;

	printf ("输入一个大写字母:");
	scanf ("%c", &ch);

	num = ch - 'A' + 1;
	for(i = 0; i < num; i++) //控制行的循环,每一行i都是一个固定值
	{
		for (i1 = 0; i1 < num - 1 - i; i1++) //控制每行的空格数
		{
			printf (" ");
		}
		for (i2 = 0; i2 <= i; i2++)  //控制每行的升序字母
		{
			printf ("%c", ch - num + 1 + i2);
		}
		for (i3 = 0; i3 < i; i3++)
		{
			printf ("%c", ch - num - 1 + i2 - i3);
		}

		printf ("\n");
	}
	return 0;
}