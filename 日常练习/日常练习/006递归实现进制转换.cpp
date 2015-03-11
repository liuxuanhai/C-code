// 利用递归实现进制的转换
#include <iostream>
#include <cstdio>
void change(long long int);
int main()
{
	using namespace std;
	long long int input;

	puts ("请输入要进行进制转换的整数: (非整数退出)");
	while (cin >> input)
	{
		if (input <= 0)
		{
			cout << "输入错误, 请输入大于0的整数!\n";
			cin.clear();
			continue;
		}
		else
		{
			cout << "二进制: "; 
			change(input);
			printf ("\n八进制: %#o\n", input);
			printf ("16进制: %#x\n", input);
		}
	}

	return 0;
}

void change(long long int input)
{
	using namespace std;
	if (input >= 2)
		change(long long int(input / 2));
	cout << input % 2;
}