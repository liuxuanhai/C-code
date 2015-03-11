// 程序清单 6.11
#include <iostream>
enum {red, orange, yellow, green, blue, violent, indigo};

int main()
{
	using namespace std;
	cout << "Enter color code (0-6): ";
	int code;
	cin >> code;
	while (code >= red && code <= indigo) // int值与枚举标签进行比较的时候会自动把枚举变量提升为int
	{
		switch (code) // 在进行int值与枚举标签进行比较的时候会自动把枚举变量提升为int
		{
			case red    : cout << "red\n";   break;
			case orange : cout << "orange\n"; break;
			case yellow : cout << "yellow\n"; break;
			case green  : cout << "green\n";  break;
			case blue   : cout << "blue\n";   break;
			case violent : cout << "violent\n";break;
			case indigo : cout << "indigo\n";  break;
			//default : cout << "can't analysis.\n"; break; // while入口条件已经限制不可能有default
		}
		cout << "Enter color code (0-6): ";
		cin >> code;
	}
	cout << "Bye!\n";
	
	return 0;
}