#include "p519继承中的动态内存分配和友元函数调用_头文件.h"
#include <cstring>

baseDMA::baseDMA(const char * l, int r)
{
	label = new char[std::strlen(l) + 1];
	std::strcpy(label, l);
	rating = r;
	std::cout << "我是baseDMA的构造方法\n";
}

baseDMA::baseDMA(const baseDMA & rs)
{  // 由于初始化的时候新对象不会调用默认构造函数而是直接调用这个复制构造函数, 所以这里label并没有被默认构造函数初始化为"null", 所以这里不用像赋值函数那样释放label的堆内存再进行赋值
	label = new char [std::strlen(rs.label) + 1];
	std::strcpy(label, rs.label);
	rating = rs.rating;   // ???????????? 为什么可以直接访问rs中的rating属性啊???????????????
}                         // 难道是本类的成员方法也可以访问其他对象的私有方法?????

baseDMA::~baseDMA()
{
	delete [] label;
}

baseDMA & baseDMA::operator=(const baseDMA & rs)// 这里虽然标示的是hasDMA类型的引用, 但是实际上它是hasDMA类型的, 本来派生类是不能访问基类私有成员的, 但是这里引用进了基类的成员方法, 所以就能使用私有属性了??????????????????????????
{
	if (this == &rs)
		return *this;
	delete [] label;  // 在进行赋值之前一定要先把之前的动态分配的内存释放掉啊
	label = new char [std::strlen(rs.label) + 1];
	std::strcpy(label, rs.label);
	rating = rs.rating;
	return *this;
}

// 基类友元函数的定义
std::ostream & operator<<(std::ostream & os, const baseDMA & rs)
{
	os << "Label: " << rs.label << std::endl;
	os << "Rating: " << rs.rating << std::endl;
	return os;
}

lacksDMA::lacksDMA(const char * c, const char * l, int r) : baseDMA (l, r)
{
	std::strncpy(color, c, 39);
	color[39] = '\0';
}

lacksDMA::lacksDMA(const char * c, const baseDMA & rs) : baseDMA(rs)
{
	std::strncpy(color, c, COL_LEN - 1);
	color[COL_LEN - 1] = '\0';
}

std::ostream & operator<<(std::ostream & os, const lacksDMA & ls)
{
	// 派生类如何使用基类的友元
	os << (const baseDMA &)ls;  // 这里如果不进行显示类型转换到话会怎么样?????????????
	os << "Color: " << ls.color << std::endl;
	return os;
}

hasDMA::hasDMA(const char * s, const char * l, int r) : baseDMA(l, r)
{
	style = new char [std::strlen(s) + 1];
	std::strcpy(style, s);
}

hasDMA::hasDMA(const char * s, const baseDMA &rs) : baseDMA(rs)
{
	style = new char [std::strlen(s) + 1];
	std::strcpy(style, s);
}

// 复制构造函数
hasDMA::hasDMA(const hasDMA & hs) : baseDMA(hs)  // 这里自动调用baseDMA(const baseDMA &)实现复制基类, 利用了多态
{
	style = new char[std::strlen(hs.style) + 1];
	std::strcpy(style, hs.style);
}

hasDMA::~hasDMA()
{
	delete [] style;
}

hasDMA & hasDMA::operator=(const hasDMA & hs)  
{
	if (this == &hs)  // 赋值的时候, 如果是自己赋给自己的话, 直接返回就成了
		return *this;
	baseDMA::operator=(hs);  // 在派生类中, 基类的复制是这么实现的!!!!!!!!!!!!!!!
							 // lackDMA中使用的是默认的赋值函数, 因为lack派生部分没用用到动态内存分配, 而默认的赋值函数会在赋值基类部分的时候调用基类的赋值函数, 所以派生类中使用默认的赋值函数时合适的
	delete [] style;  // 千万别忘了加上这个
	
	//style = hs.style;   这算个jb错误????   这跟用默认的赋值函数没什么区别了, 还是指向的堆中的同一块区域, 然后这块区域被释放了, 再次释放的时候不知道怎么释放了!!!!!!!!!!!!!!!!!
	style = new char [std::strlen(hs.style) + 1];
	std::strcpy(style, hs.style);

	return *this;
}

std::ostream & operator<<(std::ostream & os, const hasDMA & hs)
{
	// 派生类如何使用基类的友元 友元不是成员函数, 所以不能用作用域解析符来指定使用那个友元函数, 所以要用强制类型转换, 以便匹配原型的时候能够选择正确的函数
	os << (const baseDMA &) hs;  // 这样实现的调用基类的operator<<函数, 而不是调用本派生类的
	os << "Style: " << hs.style << std::endl;
	return os;
}