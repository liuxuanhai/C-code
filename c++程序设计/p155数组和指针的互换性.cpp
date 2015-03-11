// 例 7-3 数组和指针的互换性示例
#include <stdio.h>
#define SIZE 5

int main (void)
{
	int a[SIZE] = {0, 1, 2, 3, 4};
	int * aPtr = a;              // 数组a的首地址赋给指针aPtr
	int i;

	// 通过数组名和下标访问数组
	for (i = 0; i < SIZE; i++)
		printf ("\na[%d] = %d", i, a[i]);

	// 通过指针和下标访问数组
	for (i = 0; i < SIZE; i++)
		printf ("\naPtr[%d] = %d", i, aPtr[i]);
	// 通过指针和偏移量访问数组
	for (i = 0; i < SIZE; i++)
		printf ("\n*(aPtr + %d) = %d", i, *(aPtr + i));
    
	// 通过数组名和偏移量访问数组
	for (i = 0; i < SIZE; i++)
		printf ("\n*(a + %d) = %d", i, *(a + i));
	
	printf ("\n");

	return 0;
}