// 程序清单 12.5 实现文件
#include <cstring>
#include "p442string类的部分功能的实现.h"
using std::cin;
using std::cout;

// 初始化静态成员
int String::num_strings = 0;
// 静态成员函数
// 1. 不能通过对象调用静态成员函数, 实际上, 静态成员函数甚至不能使用this指针.
// 2. 如果静态成员函数是在共有部分声明的, 则可以使用类名和作用域解析运算符调用它(String::HowMany())
// 3. 由于静态成员函数不与特定的对象相关联, 因此只能使用静态数据成员
int String::HowMany()  // 静态成员函数的定义部分不能加上static
{
	return num_strings;
}
// 成员方法
String::String(const char * s)
{
	len = std::strlen(s);
	str = new char [len + 1];
	std::strcpy(str, s);
	num_strings++;
}

String::String(const String & st)
{
	num_strings++;
	len = st.len;
	str = new char [len + 1];
	std::strcpy(str, st.str);
}

String::String()
{
	len = 4;
	//str = new char [1];  // 之所以不适用str = new char;是因为前者与类析构函数兼容, 可以用delete [] str;释放内存
	//str[0] = '\0';
	// 由于delete []与使用new[]初始化的指针和空指针兼容, 因此可以直接这样写
	str = nullptr;  // 0 NULL(c语言宏) nullptr(c++关键字) 都可以表示空指针
	num_strings++;
}

String::~String()
{
	--num_strings;
	delete [] str;
}

// 运算符重载函数
	// 将一个string类赋给另一个string类
String & String::operator=(const String & st)
{
	if (this == &st)
		return *this;
	delete [] str;
	len = st.len;
	str = new char [len + 1];
	std::strcpy(str, st.str);
	return *this;
}
	// 将一个c字符串赋给一个string类
String & String::operator=(const char * s)
{
	delete [] str;
	len = std::strlen(s);
	str = new char[len + 1];
	std::strcpy(str, s);
	return *this;
}
	// 非常量string类的读写字符访问
char & String::operator[](int i)
{
	return str[i];
}
	// 常量string类的只读字符访问
const char & String::operator[](int i) const
{
	return str[i];
}

// 运算符重载友元函数
bool operator<(const String & st1, const String & st2)
{
	return (std::strcmp(st1.str, st2.str) < 0);
}

bool operator>(const String & st1, const String & st2)
{
	return st2 < st1;
}

bool operator==(const String &st1, const String & st2)
{
	return (std::strcmp(st1.str, st2.str) == 0);
}
	// string类输出
ostream & operator<<(ostream & os, const String & st)
{
	os << st.str;
	return os;
}
	// quick and dirty String input
istream & operator>>(istream & is, String & st)
{
	char temp[String::CINLIM];
	is.get(temp, String::CINLIM);
	if (is)
		st = temp;
	while (is && is.get() != '\n')
		continue;
	return is;
}