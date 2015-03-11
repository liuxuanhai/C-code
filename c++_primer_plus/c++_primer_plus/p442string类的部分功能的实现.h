// 程序清单 12.4 头文件
#ifndef STRING1_H_
#define STRING1_H_
#include <iostream>
using std::ostream;
using std::istream;
class String
{
private:
	char * str;
	int len;
	static int num_strings;  // 所有类共享的静态成员函数 // 静态成员独立于对象被保存
	static const int CINLIM = 80;  // 这里写上了值, 区别???
public:
// ===== 构造函数和其他方法 =====
	// 格式转换构造函数
	String(const char * s);
	String(const String &);
	// 默认构造函数
	String();

	~String();
	int length() const{return len;}
// ====== 运算符重载函数 ======
	String & operator=(const String &);
	String & operator=(const char *);
	// 提供以数组表示法访问字符串中各个字符的函数
	char & operator[](int i);  // 能读能改
	const char & operator[](int i) const;  // 只读
// ====== 运算符重载友元函数 ====
	friend bool operator<(const String & st, const String & st2);
	friend bool operator>(const String & st1, const String & st2);
	friend bool operator==(const String & st1, const String & st2);
	friend ostream & operator<<(ostream & os, const String & st);
	friend istream & operator>>(istream & is, String & st);
// ====== 静态成员函数 ======
	static int HowMany();
};
#endif