// p335 程序清单 12.7 (一)
#include <stdio.h>
#include <time.h>

extern int rand1 (void);
extern void srand1 (unsigned int);

int main (void)
{
	int count;
	unsigned int seed;

	//puts ("请输入种子数:");
	//while (1 == scanf_s ("%u", &seed))
	//{
		srand1 ((unsigned int)time(0));  // 重置种子
		for (count = 0; count < 5; count++)
			printf ("%hd\n", rand1 ());  // %hd short int类型
		//puts ("请输入种子数:");
	//}
	printf ("完成!\n");

	return 0;
}