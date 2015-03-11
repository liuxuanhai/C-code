// c primer plus 编程练习 8.11 p211 第八题
// 一个简单地计算器
#include <stdio.h>
int menu (void);                // 列选项, 判断choice
float get_factor (int);         // 获得操作因子
float changezero (void);        // 当除数为0时给用户重新输入的机会
int main (void)
{
	int choice;
	float fir, sec, result;

	while ((choice = menu()) != 5)
	{
		fir = get_factor (1);
		sec = get_factor (2);
		switch (choice)
		{
			case 1: result = fir + sec;
					printf ("%.2f + %.2f = %.2f\n", fir, sec, result);
					break;
			case 2: result = fir - sec;
					printf ("%.2f - %.2f = %.2f\n", fir, sec, result);
					break;
			case 3: result = fir * sec;
					printf ("%.2f * %.2f = %.2f\n", fir, sec, result);
					break;
			case 4: if(0 == sec)
						sec = changezero ();
					result = fir / sec;
					printf ("%.2f / %.2f = %.2f\n", fir, sec, result);
					break;
			default: printf ("error!");
					break;
		}
		
	}
	printf ("Bye!\n");

	return 0;
}

// 列出菜单, 判断输入
int menu (void)
{
	int input;

	printf ("要我做哪种运算?\n");
	printf ("1. +	2. -\n3. *	4. /\n5. quit!\n");
	// 判断输入
	while (scanf ("%d", &input) != 1             // 当输入为非整数时
			|| input <1  || input > 5)           // 当输入不是1-5的整数时
	{
		while (getchar() != '\n')                // 删掉多余字符
			continue;
		printf ("请输入1-5的整数!\n");
	}
	while (getchar() != '\n')                    // 即使输入1 23通过了也要删掉23防止他作为第一个因数输入进去
			continue;
	return input;	
}

// 判断输入的因子
float get_factor (int n)
{
	float input;
	
	printf ("请输入第%d个数:", n);
	while (scanf ("%f", &input) != 1)            // 当输入为非double时
	{
		while (getchar() != '\n')                // 删掉多余字符
			continue;
		printf ("请输入double类型的数字:\n");
	
	}

	return input;
}

float changezero (void)
{
	float r;
	printf ("除数不能为0,请输入非0的double类型的数字:\n");
	while (scanf ("%f", &r) != 1 || 0 == r)
	{
		while (getchar() != '\n')                // 删掉多余字符
			continue;
		printf ("除数不能为0,请输入非0的double类型的数字:\n");
	}
	return r;
}