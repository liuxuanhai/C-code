// 程序清单 6.8
#include <iostream>
#include <cctype>
int main()
{
	using namespace std;
	cout << "Enter text for analysis, and type @"
		" to terminate input.\n";
	char ch;
	int whitespace = 0;
	int digits = 0;
	int chars = 0;
	int punct = 0;
	int others = 0;
	while (cin.get(ch) && ch != '@')
	{
		if (isalpha(ch)) // 如果是字母的话
			chars++;
		else if (isspace(ch)) // 如果是空白 字符的话
			whitespace++;
		else if (isdigit(ch)) // 如果是阿拉伯数字的话
			digits++;
		else if (ispunct(ch)) // 如果是标点符号的话
			punct++;
		else
			others++;
	}
	cout << chars << " letters. ";
	cout << whitespace << " whitespaces. ";
	cout << digits << " digits. ";
	cout << punct << " punctuations. ";
	cout << others << " others.\n";

	return 0;
}