// 程序清单 12.1 头文件部分
// c++在类中默认生成的特殊成员函数:
// 1. 默认构造函数  // 没有参数或全部都是默认参数的构造函数
// 2. 默认析构函数
// 3. 复制构造函数  新建一个对象并将其初始化为同类现有对象的时候将会自动调用复制构造函数, StringBad(const StringBad &);
			 // 1. 函数按值传递对象  2. 函数返回对象  3. 创建新对象并将其初始化为同类某个对象的时候  4. 几个对象相加可能创建临时对象保存中间结果的时候
// 4. 赋值运算符
// 5. 地址运算符
#include <iostream>
#ifndef STRINGBAD_H_
#define STRINGBAD_H_

class StringBad
{
private:
	char * str;  // str指针  这里使用的是char指针而不是char数组, 这意味着类声明不会为字符串本身分配储存空间, 而是在构造函数中使用new莱维字符串分配空间
	int len;  // str长度
	static int num_strings;  // 项目个数  静态类成员的特点, 无论创建了多少对象, 程序都只创建一个静态类变量的副本.
	// 这里没有进行初始化, 没有分配内存, 而是在实现文件中进行的初始化, 这是因为类声明位于头文件中, 程序可能将头文件包括在其他几个文件中, 如果在头文件进行初始化, 将出现多个初始化语句副本, 从而引发错误
	// 列外情况是静态数据成员是整型或枚举类型const, 因为他们的链接性为内部
public:
	//====== 只有一个参数的构造函数被称作转换函数 ======
	StringBad(const char * s);  // constructor
	StringBad();  // default constructor
	~StringBad();  // destructor
	StringBad(const StringBad & st);  // 深度复制构造函数
	StringBad & operator=(const StringBad  & st);  // 深度赋值运算符重载
// friend function
	friend std::ostream & operator<<(std::ostream & os, const StringBad & st);
};

#endif

// 程序清单 12.2 实现部分
#include <cstring>
using std::cout;

int StringBad::num_strings = 0;  // 全局变量, 具有静态属性, 自动设置为零
// char StringBad::len = 3l;  // 非静态数据成员不能再类的外部定义

StringBad::StringBad(const char * s)
{
	len = std::strlen(s);
	str = new char[len + 1];
	std::strcpy(str, s);
	num_strings++;
	cout << num_strings << ": \"" << str << "\" object created\n";
}

StringBad::StringBad()
{
	len = 4;
	str = new char[4];
	std::strcpy(str, "C++");
	num_strings++;
	cout << num_strings << ": \"" << str << "\" default object created\n";
}

StringBad::~StringBad()
{
	cout << "\""<< str << "\" boject deleted, ";
	--num_strings;
	cout << num_strings << " left\n";
	delete [] str;
}

std::ostream & operator<<(std::ostream & os, const StringBad & st)
{
	os << st.str;
	return os;
}

// 深度复制构造函数
StringBad::StringBad(const StringBad & st)
{
	num_strings++;
	len = st.len;
	str = new char [len + 1];
	std::strcpy(str, st.str);
	cout << num_strings << ": \"" << str
		<< "\" object created\n";
}
// 深度赋值运算符重载
StringBad & StringBad::operator=(const StringBad & st)
{
	if (this == &st)
		return *this;  // 避免将对象赋给自身, 否则给对象重新赋值前, 释放内存操作可能删除对象内容
	delete [] str;  // 由于目标对象可能引用了以前分配的数据, 所以函数应使用delete[]来释放这些数据
	len = st.len;
	str = new char [len + 1];
	std::strcpy(str, st.str);
	return *this;
}

// 程序清单 12.3 客户文件
#include <iostream>
using std::cout;

void callme1(StringBad &);
void callme2(StringBad);

int main()
{
	using std::endl;
	{
		cout << "Starting an inner block.\n";
		StringBad headline1("Celery Stalks at Midnight");
		StringBad headline2("Lettuce Prey");
		StringBad sports("Spinach Leaves Bowl for Dollars");
		puts("");

		cout << "headline1: " << headline1 << endl;
		cout << "headline2: " << headline2 << endl;
		cout << "sports: " << sports << endl;
		puts("");

		callme1(headline1);
		cout << "headline1: " << headline1 << endl;
		callme2(headline2);  // 在这里开始出错了 
		cout << "headline2: " << headline2 << endl;
		puts("");

		cout << "Initialize one objict to another: \n";
		StringBad sailor = sports;  // 等效于StringBad sailor = StringBad(sports);  // 它使用的是复制构造函数 StringBad(const StringBad &); const 要注意 自动生成的构造函数不知道要自增string_num++
			// 调用了隐式复制函数和隐式赋值运算符函数
		cout << "sailor: " << sailor << endl;
		puts("");

		cout << "Assign one object to another: \n";
		StringBad knot;
		knot = headline1;
		cout << "knot: " << knot << endl;
		puts("");
		
		cout << "Exiting the block.\n";
	}
	cout << "End of main()\n";

	return 0;
}

void callme1(StringBad & rsb)
{
	cout << "String passed by reference:\n";
	cout << "   \"" << rsb << "\"\n";
}

void callme2(StringBad sb)  // 每当程序生成了对象的副本时, 编译器就会调用复制构造函数:
{                                       // 1. 函数按值传递对象  2. 函数返回对象  3. 创建新对象并将其初始化为同类某个对象的时候  4. 几个对象相加可能创建临时对象保存中间结果的时候
	cout << "String passed by value: \n";
	cout << "   \"" << sb << "\"\n";
}