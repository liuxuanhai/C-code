// 程序清单 4.10
#include <iostream>
#include <string>   // make string class available
#include <cstring>  // C-style string library
int main()
{
	using namespace std;
	char charr[20];
	string str;

	cout << "Length of string in charr before input: "
		 << strlen(charr) << endl; // 未初始化的字符串长度是未知的, 看数组外随机'\0'的位置了
	cout << "Length of string in str before input: "
		 << str.size() << endl;
	cout << "Enter a line of text:\n";
	cin.getline(charr, 20); // indicate(表明象征指示) maximum length
	cout << "You entered: " << charr << endl;
	cout << "Enter another line of text: \n";
	getline(cin, str);
	cout << "You entered: " << str << endl;
	cout << "Length of string in charr after input: "
		 << strlen(charr) << endl;
	cout << "Length of string in str after input: "
		 << str.size() << endl;

	return 0;
}