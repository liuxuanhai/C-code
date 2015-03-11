//ascii值查询器
#include <stdio.h>
int main (void)
{
	char input;

	printf ("请输入要查询ascii码的符号: \n");
	while(scanf ("%c", &input) == 1)
	{
		if(input != 10)
		{
			printf ("%c -> %d\n", input, input);
		}
	}
	return 0;
}