// 程序清单 9.9
#include <iostream>
// constants(常量)
const int ArSize = 10;
// function prototype(原型)
extern "C++" void strcount(const char * str); // extern 说明其为外部链接静态函数, extern是可选的, 可以用static覆盖为只在本文件使用
	// "c++" 说明符指出使用的是"c++"的语言链接性
extern const int i = 1;

int main()
{
	using namespace std;
	char input[ArSize];
	char next;

	cout << "Enter a line:\n";
	cin.get(input, ArSize);  // 最多输入ArSize个字符, 不读入换行符并把它留在输入队列
	while (cin)             // 试图用cin.get(char *, int); 读取空行将会导致cin为false
	{
		cin.get(next);
		while (next != '\n') // string didn't fit!(合适)
			cin.get(next);   // dispose(处理) of remainder 
		strcount(input);
		cout << "Enter next line (empty line to quit):\n";
		cin.get(input, ArSize);
	}
	cout << "Bye.\n";

	return 0;
}

void strcount(const char * str)
{
	using namespace std;
	static int total = 0;  // static local variable
	int count = 0;         // auto local variable

	cout << "\"" << str << "\" contains ";
	while (*str++)   // go to end of string
		count++;
	total += count;
	cout << count << " characters\n";
	cout << total << " characters total\n";
}