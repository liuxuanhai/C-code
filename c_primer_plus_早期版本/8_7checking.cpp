// 输送-1000 - 1000的整数, 计算他们的平方和     目的: 排除用户的错误输入,使程序更友好的练习
// c primer plus 程序清单 8_7 p202
// check.c -- 输入确认
#include <stdio.h>
// 确认输入了一个整数
int get_int (void);
// 确认范围的上下界是否有效
int bad_limits (int begin, int end, int low, int hight);
// 计算从a到b之间的整数的平方和
double sum_squares (int a, int b);
int main (void)
{
	const int MIN = -1000;  // 范围的下界限制
	const int MAX = 1000;   // 范围的上届限制
	int start;              // 范围的上界
	int stop;               // 范围的下界
	double answer;          // 平方和

	printf ("This program computes the sum of squares of "
		    "integers in a rang.\nThe lower bound should not "
			"be less than -1000 and\nthe upper bound should not"
			" be more than 1000.\nEnter the limits (enter 0 for "
			"both limits to quit):\nlower limits: \n");
	start = get_int ();
	printf ("upper limit: \n");
	stop = get_int ();
	while (start != 0 || stop != 0)
	{
		if (1 == bad_limits (start, stop, MIN, MAX))
			printf ("please try again.\n");
		else
		{
			answer = sum_squares (start, stop);
			printf ("The sum of the squares of the integers from %d to %d is %g.\n",
				     start, stop, answer);
		}
		printf("Enter the limits (enter 0 for both limits to quit):\nlower limits: \n");
		start = get_int ();
	    printf ("upper limit: \n");
		stop = get_int ();
	}
	printf ("Bye!\n");
	return 0;
}
int get_int (void)
{
	int input;
	char ch;

	while (scanf("%d", &input) != 1)         // 如果输入的不是int整数,将要不停的循环,因为他的判断就是个输入scanf()
	{
		while ((ch = getchar()) != '\n')     // 如果输入的字符不是空格将要...
			putchar (ch);                    // 剔除错误的输入    //输入的东西将不会再读入下一次读取,删除后比如输入low
		printf (" is not an integer.\nPlease enter "                 //将会不停的显示下面的printf语句因为scanf不能
			    "an integer value, such as 25, -178, or 3: \n");          //把l读进去,所以将不停的执行循环去尝试读l,而加上
	}                                                                    //这句话后会用getchar读入low并什么都不做,但是
	return input;                                                           //low被读入一次后将不会再下次被读入了
}
int bad_limits (int begin, int end, int low, int high)
{
	int not_good = 0;

	if (begin > end)             // 如果输入的第一个数小于第二个数
	{
		printf ("%d isn't smaller than %d.\n", begin, end);
		not_good = 1;
	}
	if (begin < low || end < low)             // 如果输入数小于左边界
	{
		printf ("Values must be %d or greater.\n", low);
        not_good = 1;
	}
	if (begin >high || end > high)             // 如果输入数大于右边界
	{
		printf ("Values must be %d or less.\n", high);
		not_good = 1;
	}
	return not_good;
}
double sum_squares (int a, int b)
{
	double total = 0;
	int i;

	for (i = a; i <= b; i++)
		total += i * i;
	
	return total;
}