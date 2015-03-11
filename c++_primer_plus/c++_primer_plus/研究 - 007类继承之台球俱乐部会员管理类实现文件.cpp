#include "007研究 - 类继承之台球俱乐部会员管理类.h"
#include <iostream>

TableTennisPlayer::TableTennisPlayer(const string & fn, 
									 const string & ln, 
									 bool ht) : 
strFirstName(fn), strLastName(ln), isHasTable(ht) {}	// 这里使用初始化列表, 将步骤: 默认构造函数->赋值运算符 改成了 复制转换构造函数 这一步.

void TableTennisPlayer::ShowName() const
{
	std::cout << strLastName << ", " << strFirstName;
}

RatedPlayer::RatedPlayer(unsigned int r, const string & fn, const string & ln, bool ht) : TableTennisPlayer(fn, ln, ht)
{																					// 成员初始化列表, 他是可执行代码, 会在调用派生类之前调用此基类方法
																					// 如果不调用基类构造函数, 把上边的代码注释了, 程序会调用默认的基类构造函数
	//TableTennisPlayer(fn, ln, ht);	// 这样写是不行的, 必须将创建的基类对象嵌套在派生类中
										// 在这里这样写是没用的, 这里只是显式生成了一个基类对象, 这个对象并没有嵌套进派生类中
										// C++的内部机制是在生成派生类对象之前生成基类对象, 使用下边的这种方法是嵌套不进去的
	//this->TableTennisPlayer = TableTennisPlayer(fn, ln, ht);	// 无法将基类嵌套进派生类

	rating = r;
}

RatedPlayer::RatedPlayer(unsigned int r, const TableTennisPlayer & tp) : TableTennisPlayer(tp)
{
	rating = r;
}