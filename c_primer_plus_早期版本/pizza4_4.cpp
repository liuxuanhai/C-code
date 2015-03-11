//c primer plus 程序清单4.4
//pizza.c  --  在这个披萨饼的例子中使用定义常量
#include <stdio.h>
#define PI 3.14159
int main ()
{
	float area,circum,radius;  //area 面积 circum 周长 radius 半径

	printf ("What is the radius of your pizza?\n");
	scanf ("%f",&radius);
	area = PI * radius * radius;
	circum = 2.0 * radius * PI;
	printf ("Your basic pizza parameters are as follows:\n");
	printf ("circumference = %1.2f,area = %1.2f \n",circum,area);
	return 0;
}