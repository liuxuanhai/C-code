// 通过对for循环条件的更改实现用户控制循环次数
#include <stdio.h>
int main(void)
{
	int input = 5;
	int p = 1;

	for(int i = 0; i < input; i++)
	{
		printf("#\n");
		if(1 == p)
		{
			puts("How many times do you wanna to loop:");
			scanf("%d", &input);
			p = 0;
		}
	}

	return 0;
}