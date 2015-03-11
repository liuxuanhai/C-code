// 指针运算的优先级                        *ar++ *++ar 
// c primer plus 程序清单 10.12 p259
// order.c -- 指针运算的优先级
#include <stdio.h>
int data[2] = {100, 200};
int moredata[2] = {300, 400};
int main (void)
{
	int * p1, * p2, * p3, * p4;

	p1 = p2 = data;
	p3 = moredata;
	printf (" *p1 = %d, *p2 = %d, *p3 = %d\n", *p1, *p2, *p3);// 一元运算符*和++具有相同的优先级,但在结合时是 从右向左 进行的
	printf ("*p1++= %d, *++p2=%d,(*p3)++=%d\n", *p1++, *++p2, (*p3)++);
	printf (" *p1 = %d, *p2 = %d, *p3 = %d\n", *p1, *p2, *p3);
	
	return 0;
}