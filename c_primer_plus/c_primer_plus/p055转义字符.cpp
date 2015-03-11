// 程序清单 3.10
// 使用转义字符
#include <stdio.h>
int main (void)
{
	float salary;
	printf ("\aEnter your desire monthly salary: ");
	printf ("$_______\b\b\b\b\b\b\b");
	scanf ("%f", &salary);
	printf ("\n\t$%.2f a month is $%.2f a year.", salary, salary * 12);
	printf ("\rGee!\n");

	return 0;
}