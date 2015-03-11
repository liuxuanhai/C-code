// 程序清单 10.6
// 关于为什么c会允许超出数组边界的使用的情况的发生: 在程序运行之前, 索引的值有可能尚未完全确定下来, 所以编译器此时不能找出所有索引的错误
// 为保证程序正确运行, 编译器必须在程序运行时添加检查每个索引是否合法的代码, 这回导致程序的运行速度减慢
#include <stdio.h>
#define SIZE 4
int main(void)
{
	int value = 44;
	int arr[SIZE]; // 分配了内存 但是内存里面没有值
	int value2 = 88;
	int i;

	printf("%p %p %p %p", &value, &arr[0], &arr[1] , &value2);
	printf("value = %d, value2 = %d\n", value, value2);
	for (i = -1; i <= SIZE; i++)  // 赋值的时候超越数组会使得数组周围的栈遭到破坏, c给予程序猿这种自由, 但是vs2012会在进行赋值后
								// 进行报错, Run-Time Check Failure #2 - Stack around the variable'arr' was corrupted
								// Run-Time: 固定词组 ph. 1.运行电脑的时间;电脑运作其他意思1.加工(运行)时间2.执行时期3.程序运行时
								// Check Failure 检查失败 variable变量 corrupted 损坏 stack 栈
		arr[i] = 2 * i + 1;
	//arr[-3] = 111;                // 注意到书上数组两边直接是value和value2的值而我测试的时候两边却各有野值8字节, 而且书上能够赋值而我不能给野值赋值却能更改value的值
	//arr[-4] = 222;                 // 也能更改以外的值, 所以推断他的检查机理就是保护arr周围的8字节野值    
	for (i = -5; i < 9; i++)
		printf("%2d %d\n", i, arr[i]);
	printf("value = %d, value2 = %d\n", value, value2);

	return 0;
}