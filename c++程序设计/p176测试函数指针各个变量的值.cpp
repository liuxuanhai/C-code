// 测试函数指针各个变量的值
#include <stdio.h>
#include <iostream.h>
int f (char);                     // 声明一个函数
int main ()
{
	int (* fp)(char);             // 声明一个函数指针
	int arr[] = {1, 2};
	int num = 3;

	printf ("f对应函数的首地址,f == %p\n"
		     "arr对应数组的首地址,arr == %p\n"
			 "num == %p\n", f, arr, num);
	printf ("f的地址,&f == %p\n"
		    "arr的地址,&arr == %p\n"
			"num的地址,&num == %p\n", &f, &arr, &num);

	printf ("%p, %p\n", arr, &arr/*(&arr)[0]*/);  // ??????????????????????// 虽然他们的值相同,但是他们指向的对象是不同的,arr是编译器为整个数组的命名编译器设置它为第一个数组的地址而不是像变量一样为一个值?????/
	printf ("....%d.......", *arr);
	
	fp = f;
	printf ("fp=f后fp对应的值,fp == %p\n", fp);
	return 0;
}

int f (char c)
{
	printf ("%c", c);
	
	return 1;
}