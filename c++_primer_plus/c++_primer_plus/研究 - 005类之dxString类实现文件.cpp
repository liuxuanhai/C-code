#include <cstring>
#include "研究 - 005类之dxString类.h"

using std::cout;
int dxString::num_string = 0;	// 初始化指出了类型, 并使用了作用域运算符, 但是没有使用关键字static
								// 初始化位于方法文件中, 而不是类声明文件中;
// char StringBad::len = 3l;	// 非静态数据成员不能再类的外部定义

	// 静态成员方法定义
int dxString::HowMany()	// 声明中加上static, 定义中不用加
{
	return num_string;
}

dxString::dxString(const char * s)
{
	len = std::strlen(s);
	str = new char[len + 1];
	std::strcpy(str, s);
	num_string++;
	cout << num_string << ": \"" << str << "\" 项目被创建.\n";
}

dxString::dxString()
{
	len = 4;
	str = new char[len];
	std::strcpy(str, "C++");
	num_string++;
	cout << num_string << ": \"" << str << "\" 项目被创建.\n";
}

dxString::~dxString()
{
	cout << "\"" << str << "\" 项目被删除, " << --num_string << " 被剩下.\n";
	delete []str;
}

std::ostream & operator<<(std::ostream & os, const dxString & st)
{
	os << st.str;
	return os;
}

std::istream & operator>>(std::istream & is, dxString & st)
{
	char temp[dxString::CINLIM];
	is.get(temp, dxString::CINLIM);
	if (is)
		st = temp;
	while (is && is.get() != '\n')
		continue;
	return is;
}

// 深度复制构造函数
dxString::dxString(const dxString & st)
{
	num_string++;
	len = st.len;
	str = new char[len + 1];
	std::strcpy(str, st.str);
	cout << num_string << ": \"" << str << "\" 项目被创建.\n";
}

// 深度赋值运算符重载
dxString & dxString::operator=(const dxString & st)
{
	if (this == &st)	// 避免将对象赋给自身, 因为在对象重新赋值之前, 会首先释放被赋值对象的静态区内存, 这样, 就会使得被赋予不存在的内存;
		return *this;
	delete [] str;		// 把对象之前保存的静态区数据释放掉;
	len = st.len;
	str = new char[len + 1];
	std::strcpy(str, st.str);
	return *this;
}

dxString & dxString::operator=(const char * pch)
{
	delete [] str;
	len = std::strlen(pch);
	str = new char[len + 1];
	std::strcpy(str, pch);
	return *this;
}

char & dxString::operator[](int i)
{
	return str[i];
}

const char & dxString::operator[](int i) const
{
	return str[i];
}

bool operator<(const dxString & st1, const dxString & st2)
{
	return (std::strcmp(st1.str, st2.str));
}

bool operator>(const dxString & st1, const dxString & st2)
{
	return st2 < st1;
}

bool operator==(const dxString & st1, const dxString & st2)
{
	return (std::strcmp(st1.str, st2.str) == 0);
}