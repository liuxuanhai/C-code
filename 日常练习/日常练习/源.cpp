// char 常量在c和c++中的不同
// char ch = 'A';
// c: 常量'A'储存在一块大小与int相同的内存中, 相同的数值也被储存在变量ch中, 但是在ch中它只占据一个字节
// c++: 'A'和ch都是用一个字节
#include <stdio.h>

int main(void)
{
	int x = 'ABCD';  // 'ABCD'意存储味着一个四字节的int值, 其中第一个字节存储字母A的字符编码, 第二个字节存储B的字符编码...
		// 'ABCD' 是一个字符, 还是个常量, 正好在c环境中按四字节储存
	char c = 'ABCD';
	char f = 'AB';
	printf("%d %d %c %c %c\n", x, 'ABCD', c, 'ABCD', f);
	printf("%d %d %d %d",sizeof('A'), sizeof('AB'), sizeof('ABC'), sizeof('ABCD'));

	return 0;
}