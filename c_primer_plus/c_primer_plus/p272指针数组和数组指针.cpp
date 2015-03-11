// 自己的思考 指针数组和数组指针
#include <stdio.h>
void show_st (char (* st)[5]);
int main (void)
{
	const char * str[2] = {  // 指针数组 必须在初始化的时候给定指针的值
		"string",
		"string1"
	};
	char (* st)[5];         // 数组指针 在进行声明的时候用得着 可以告诉函数指针指向的空间大小void show_st (char (* st)[5]);表示为参数st指向5个char的空间大小
							// 函数指针 和 指针函数也是这么个道理
	char s[2][5] = {
		{"str"},
		{"str1"}
	};

	puts (str[1]);
	st = s;
	show_st (s);

	return 0;
}

void show_st (char (* st)[5])
{
	puts (st[0]);
}