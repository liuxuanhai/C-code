// 程序清单 4.8
#include <iostream>
#include <string>      // make string class available
// string类具有自动调整大小的功能
int main()
{
	using namespace std;
	string str1 = "penguin";
	string str2, str3;

	cout << "string类能够实现字符串的赋值:(str2 = str1)\n";
	str2 = str1;
	cout << "str1 = " << str1 << endl;
	cout << "str2 = " << str2 << endl; 
	cout << "string类能合并(+)并赋值(=):（str3 = str1 + str2）\n";
	str3 = str1 + str2;
	cout << str3 << endl;
	cout << "string类甚至能使用+=符号:str1 += str2\n";
	str1 += str2;
	cout << str1 << endl;
	cout << "string类还可以实现 str2 += \" for a day\": \n ";
	str2 += " for a day";
	cout << str2 << endl;

	return 0;
}