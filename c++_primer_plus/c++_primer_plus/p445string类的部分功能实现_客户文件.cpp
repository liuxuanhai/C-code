// 程序清单 12.6 客户文件
#include <iostream>
#include "p442string类的部分功能的实现.h"

const int ArSize = 10;
const int MaxLen = 81;

int main()
{
	using std::cout;
	using std::cin;
	using std::endl;
    String name;
	String name2;
	
	cout << "Hi, what's your name?\n";
	cin >> name;
	name2 = name;  // 1. 程序使用构造函数Sting(const char *)来创建一个临时string对象, 其中包含temp中的字符串副本  2. 使用String & String::operator=(const String &)函数将临时对象中的信息复制到name对象中  3. 程序调用析构函数~String()删除临时对象
	cout << name2 << ", please enter up to " << ArSize
		<< " short sayings <empty line to quit>:\n";
	String saying[ArSize];
	char temp[MaxLen];
	int i;
	for (i = 0; i < ArSize; i++)
	{
		cout << i+1 << ": ";
		cin.get(temp, MaxLen);
		while (cin && cin.get() != '\n')
			continue;
		if (!cin || temp[0] == '\0')
			break;
		else
			saying[i] = temp;
	}
	int total = i;

	if (total > 0)
	{
		cout << "Here are your sayings: \n";
		for (i = 0; i < total; i++)
			cout << saying[i][0] << ": " << saying[i] << endl;

		int shortest = 0;
		int first = 0;
		for (i = 0; i < total; i++)
		{
			if (saying[i].length() < saying[shortest].length())
				shortest = i;
			if (saying[i] < saying[first])
				first = i;
		}
		cout << "Shortest saying: \n" << saying[shortest] << endl;
		cout << "First alphabetically: \n" << saying[first] << endl;
		cout << "This program used " << String::HowMany()  // 调用静态成员函数的方法
			<< " String objects. Bye.\n";
	}
	else
		cout << "No input! Bye.";

	return 0;
}