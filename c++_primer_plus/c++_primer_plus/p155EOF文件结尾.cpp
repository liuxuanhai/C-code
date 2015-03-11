// 程序清单 5.18
#include <iostream>
int main(void)
{
	using namespace std;
	char ch;
	int count = 0;
	//cin.get(ch);
	while (EOF != (ch = cin.get())) // 当cin.get()没有参数的时候, 将会返回读取的字符
	//while (cin.get(ch))
	//while (cin)                // 由于cin.get(char)返回值是一个cin对象然后istream类提供了一个可以将istream对象(如cin)转换成bool值的函数, 当cin出现在需要bool值的地方时, 该函数将被调用, 另外 如果读取成功了返回值为true否则为false
	//while (cin.fail() == false) // text for EOF
	{
		//cout << ch;           // echo character
		++count;
		//cin.get(ch);
	}
	cout << endl << count << " characters read\n";

	return 0;
}
// 如果输入如下:
// 12[ctrl+z]34
// [ctrl+z]
// 那么统计出来的是 3个字符, 他只统计了12[ctrl+z]
// ###### 模拟EOF的字符组合是[Ctrl+z]+[Enter]