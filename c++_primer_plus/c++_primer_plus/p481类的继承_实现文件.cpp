// 程序清单 13.2  程序清单 13.5
#include "p481类的继承_头文件.h"
#include <iostream>

TableTennisPlayer::TableTennisPlayer(const string & fn, const string & ln, bool ht):firstname(fn), lastname(ln), hasTable(ht){}  // 初始化列表语法??????????????
//TableTennisPlayer::TableTennisPlayer(const string & fn, const string & ln, bool ht)
//{
//	firstname = fn;
//	lastname = ln;
//	hasTable = ht;
//}
// 这里的构造函数使用了第十二章介绍的成员初始化列表语法, 也可以使用下面的方法, 这首先为firstname调用string的默认构造函数, 在调用string的赋值运算符, 将firstname设置为fn, 但是初始化列表语法可以减少一个步骤, 他直接使用string的复制构造函数将firstname初始化为fn

void TableTennisPlayer::Name() const
{
	std::cout << lastname << ", " << firstname;
}

RatedPlayer::RatedPlayer(unsigned int r, const string & fn, const string & ln, bool ht) : TableTennisPlayer(fn, ln, ht)
{                                                                                  //  成员初始化列表, 他是可执行代码, 会在调用派生类之前调用此基类方法
	                                                                               // 如果不调用基类构造函数, 把上面的初始化列表代码注视了, 程序会调用默认的基类构造函数
	//TableTennisPlayer(fn, ln, ht);  // 这样写是不行的, 必须将创建的基类对象嵌套在派生类中
	// this.TableTennisPlayer = TableTennisPlayer(fn, ln, ht);
	rating = r;
}

RatedPlayer::RatedPlayer(unsigned int r, const TableTennisPlayer & tp) : TableTennisPlayer(tp), rating(r)
{                                                                  // 将tp传给了初始化列表的基类构造函数, 这里我们没有定义只有一个本类对象的参数, 系统会自动生成一个复制构造函数(当类内有动态分配内存的话自动生成的复制构造函数是不合适的)         
	rating = r;
}