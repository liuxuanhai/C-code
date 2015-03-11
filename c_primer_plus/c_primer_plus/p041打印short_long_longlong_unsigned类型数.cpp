// 程序清单 3.4
#include <stdio.h>
int main (void)
{
	unsigned int unint = 3000000000; // int 的范围最大可达到 '亿'
	unsigned int un = 123456789;
	short shint = 200;
	unsigned short end = 100;
	long big = 65537;
	long long verybig = 12345678908642;
	printf ("unint = %u not is %d\n", unint, unint);
	printf ("un = %u not is %ud\n\n", un, un);
	printf ("shint = %hd and %d\n", shint, shint); // 之所以可以用%d表示short类型是因为short类型在进行参数传递的时候自动变换为int类型, 因为int类型被认为是计算机处理起来最方便有效的整型
	printf ("end = %hu and %u\n\n", end, end);
	printf ("big = %ld and not %hd\n", big, big);  // 用%hd说明符只会显示他的后16位
	printf ("verybig = %lld and not %ld", verybig, verybig);
	return 0;
}