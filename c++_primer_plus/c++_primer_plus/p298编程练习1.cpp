// 编程练习 8.8
#include <iostream>
void show(const char *, int = 0); // 千万别忘了加上const
int main()
{
	char * str = "daxiong";
	show(str);
	for (int i = 0; i < 5; i++)
		show(str, i);

	return 0;
}
void show(const char *str, int n)
{
	int i;
	static int temp = 1;
	std::cout << std::endl;
	i = temp++;
	if (n != 0)
		for (; i > 0; i--)
			std::cout << str << std::endl;
	else
		std::cout << "参数为0不能打印.\n";
}