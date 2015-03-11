// 程序清单 4.11
// 不匹配的整数类型转换以及分析
#include <stdio.h>
#include <limits.h>
#define INT336 336
#define INT65618 65618
int main(void)
{
	short sh = INT336;
	short _sh = -INT336;
	printf ("unsigned short 的最大值为%d\n", USHRT_MAX);
	printf ("sh %%hd = %hd, sh %%hu = %hu\n", sh, sh);     // 在数字小于65536/2-1的情况下有无符号都一样
	printf ("-sh %%hd = %hd, -sh %%hu = %hu\n", _sh, _sh); // 65200出现的原因 系统使用被称为2的补码的方法来表示有符号整数
														   // 在这种方法中, 数字0-32767代表它本身, 而数字32768到65535代表负数. 65535代表-1 65534代表-2
														   // 所以, -336在表示为unsigned short的时候为65536 - 336
	printf ("sh %%d = %d, sh %%c = %c\n", sh, sh);         // 之所以出现'P'的原因: short int 336 二进制为 0000 0001 0101 0000
														   // 而使用%c的时候就会截取最后8位(相当于256除一个整数取其余数)80即为:P
														   // 至于为什么%d多截取了16位却为出错我就不知道了, 暂且以为不能超过16位多截取吧
	printf ("INT65618 %%d = %d, INT65618 %%hd = %hd, INT65618 %%c = %c", INT65618, INT65618, INT65618);
														   // 系统根据65618的大小把他储存为4字节的整数值当使用%hd的时候相当于取最后16的值(除以65536的余数)即82.
														   // 注意: 在32767到65536之间的数字会被打印成负数

	return 0;
}