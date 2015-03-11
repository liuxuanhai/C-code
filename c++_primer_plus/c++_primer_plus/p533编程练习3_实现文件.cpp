#include "p533编程练习3_头文件.h"
#include <cstring>
using namespace std;

// ============= ABC ==================
ABC::ABC(const char * l, int ra)
{
	label = new char[strlen(l) + 1];
	std::strcpy(label, l);
	rating = ra;
}

ABC::~ABC()
{
	delete [] label;
}

ABC & ABC::operator=(const ABC & abc)
{
	if (&abc == this)
		return *this;

	delete [] label;
	label = new char[strlen(abc.label) + 1];
	strcpy(label, abc.label);
	rating = abc.rating;
	return *this;
}

ABC::ABC(const ABC & abc)
{
	label = new char[strlen(abc.label) + 1];
	strcpy(label, abc.label);
	rating = abc.rating;
}

void ABC::View() const
{
	cout << "Label: " << label << endl;
	cout << "Rating: " << rating << endl;
}

std::ostream & operator<<(ostream & os, const ABC & abc)
{
	abc.View();  // 派生类用的话会调用相应的派生类的View
	return os;
}

// =============== baseDMA =====================

baseDMA::baseDMA(const char * l, int r) : ABC(l, r)
{
}
// =============== lacksDMA ====================

lacksDMA::lacksDMA(const char * c, const char * l, int r) : ABC (l, r)
{                                                        // 这里基类的复制构造函数不写的话会自动调用, 但是调用的是没有参数的默认的构造函数, 如果需要进行初始化的话就要加上初始化列表的了
	std::strncpy(color, c, 39);
	color[39] = '\0';
}

lacksDMA::lacksDMA(const char * c, const ABC & rs) : ABC(rs)
{
	std::strncpy(color, c, COL_LEN - 1);
	color[COL_LEN - 1] = '\0';
}

void lacksDMA::View() const
{
    ABC::View();
    std::cout << "Color: " << color << std::endl;
}

// ================ hasDMA ================

hasDMA::hasDMA(const char * s, const char * l, int r) : ABC(l, r)
{
	style = new char [std::strlen(s) + 1];
	std::strcpy(style, s);
}

hasDMA::hasDMA(const char * s, const ABC & rs) : ABC(rs)
{
	style = new char [std::strlen(s) + 1];
	std::strcpy(style, s);
}

// 复制构造函数
hasDMA::hasDMA(const hasDMA & hs) : ABC(hs)  // 这里自动调用baseDMA(const baseDMA &)实现复制基类, 利用了多态
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
	ABC::operator=(hs);  // 在派生类中, 基类的复制是这么实现的!!!!!!!!!!!!!!!
							 // lackDMA中使用的是默认的赋值函数, 因为lack派生部分没用用到动态内存分配, 而默认的赋值函数会在赋值基类部分的时候调用基类的赋值函数, 所以派生类中使用默认的赋值函数时合适的
	delete [] style;  // 千万别忘了加上这个
	
	//style = hs.style;   这算个jb错误????   这跟用默认的赋值函数没什么区别了, 还是指向的堆中的同一块区域, 然后这块区域被释放了, 再次释放的时候不知道怎么释放了!!!!!!!!!!!!!!!!!
	style = new char [std::strlen(hs.style) + 1];
	std::strcpy(style, hs.style);

	return *this;
}

void hasDMA::View() const
{
    ABC::View();
    std::cout << "Style: " << style << std::endl;
}