// p426开始 462结束

// c++在类中默认生成的特殊成员函数:
// 1. 默认构造函数  // 没有参数或全部都是默认参数的构造函数
// 2. 默认析构函数
// 3. 复制构造函数  新建一个对象并将其初始化为同类现有对象的时候将会自动调用复制构造函数, StringBad(const StringBad &);
			 // 1. 函数按值传递对象  2. 函数返回对象  3. 创建新对象并将其初始化为同类某个对象的时候  4. 几个对象相加可能创建临时对象保存中间结果的时候
// 4. 赋值运算符
// 5. 地址运算符

#include <iostream>
#ifndef  dxString_H_
#define  dxString_H_

class dxString
{
private:
	char *		str;
	int			len;
	static int	num_string;
	static const int CINLIM = 80;	// 静态 常量 可以直接赋值
public:
	dxString(const char * s);		// 转换构造函数
	dxString();	// 默认构造函数
	dxString(const dxString & st);	// 深度复制构造转换函数
									// 1. 显式初始化对象
									// 2. 也能用于按值传递的时候, 对新对象参数进行初始化
									// 3. 返回对象
									// 4. 对象相加生成临时对象保存中间值
	~dxString();

	int length() const {return len;}

	dxString & operator=(const dxString & st);	// 如果传的是char * pch如果通过这个函数实现的话还需要将pch通过转换构造函数生成临时变量, 然后把临时变量引用给参数, 太麻烦了, 所以重载一个char * 的函数很有必要
	dxString & operator=(const char * pch);
	char		& operator[](int i);
	const char	& operator[](int i) const;

	friend bool operator< (const dxString & st1, const dxString & st2);
	friend bool operator> (const dxString & st1, const dxString & st2);
	friend bool operator==(const dxString & st1, const dxString & st2);
	
	friend std::ostream & operator<<(std::ostream & os, const dxString & st);
	friend std::istream & operator>>(std::istream & is, dxString & st);

		// 静态成员方法
	static int HowMany();	// 定义中不用加static
							// 不能通过对象调用静态成员函数(类名加作用域解析符调用), 静态成员函数不能使用this指针;
							// 静态成员函数不与特定对象相关联, 因此只能使用静态数据成员, 他不能访问len;
							// 可以通过静态成员函数设置类级(classwide)标记, 以控制某些接口的行为;
};

#endif