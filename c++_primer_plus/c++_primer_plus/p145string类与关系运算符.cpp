// 程序清单 5.12
// 关于c风格的字符串比较和c++风格的字符串比较
#include <iostream>
#include <string>   // string class
#include <cstring>  // strcmp()
int main()
{
	using namespace std;

// ###### c-style #######
	char word1[5] = "?ate";
	for (char ch = 'a'; strcmp(word1, "mate"); ch++)
	{
		cout << word1 << endl;
		word1[0] = ch;
	}
	cout << "最终结果:" << word1 << endl;

	string word2 = "?ate";
	for (char ch = 'a'; word2 != "mate"; ch++)
	{
		cout << word2 << endl;
		word2[0] = ch;
	}
	cout << "string的方法最终结果:" << word2 << endl;

	return 0;
}