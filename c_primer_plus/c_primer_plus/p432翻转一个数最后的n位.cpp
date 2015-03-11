// 程序清单 15.2
#include <stdio.h>

char * itobs (int, char *); // 字符指针函数(返回值为指针)
void show_bstr (const char *);
int invert_end (int num, int bits);

int main (void)
{
	char bin_str[8 * sizeof (int) + 1]; // int 4个字节, 每个字节8位, 所以乘以8
	int number;

	puts ("输入数字, 我给出你他的二进制形式.");
	while (scanf ("%d", &number) == 1)
	{
		itobs (number, bin_str);
		printf ("%d is ", number);
		show_bstr (bin_str);
		putchar ('\n');
		number = invert_end (number, 4);
		printf ("反置最后四位:\n");
		show_bstr (itobs (number, bin_str));
		putchar ('\n');
	}
	puts ("Done!");

	return 0;
}

char * itobs (int n, char * ps)
{
	int i;
	static int size = 8 * sizeof (int);

	for (i = size - 1; i >= 0; i--, n >>= 1)
		ps[i] = (01 & n) + '0'; // 01 为一个八进制掩码的表示方式, 该掩码除位0之外的所有位都设置为0
	ps[size] = '\0';

	return ps;
}

// 四位一组显示二进制字符串
void show_bstr (const char * str)
{
	int i = 0;
	while (str[i]) // 不是一个空的字符
	{
		putchar (str[i]);
		if (++i % 4 == 0 && str[i])
			putchar (' ');
	}
}

int invert_end (int num, int bits)
{
	int mask = 0;
	int bitval = 1;

	while (bits-- > 0)
	{
		mask |= bitval;
		bitval <<= 1;
	}
	return num ^ mask;
}