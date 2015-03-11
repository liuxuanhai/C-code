#include <iostream>
#include <string>
using namespace std;

int main()
{
	string str;	// 一个空的string
	cout << str << endl;
	str = "0123456789";
	cout << str << endl;
	string str1(str);	// copy构造函数, 生成str的一个复制品
	cout << str1 << endl;
	string str3(str, 1);	// 将str中始于位置3的部分当作str3的初值 !!!第二个参数是索引, 以0开始
	cout << str3 << endl;
	string str4(str, 4, 3);
	cout << str4 << endl;	// 第二个参数是索引idx, 第三个参数是长度len
	string str5("const char *(C-string)");	// 使用C-string作为字符串str5的初值
	cout << str5 << endl;
	string str6("const char *(C-string)", 5);	// 以C-string的前5个字符作字符串str6初值
	cout << str6 << endl;
	string str7(5, 'C');	// 生成一个字符串, 包含5个'C'
	cout << str7 << endl;
	string str8(str.begin() + 1, str.begin() + 3);	// [beg, end)
	cout << str8 << endl;
}