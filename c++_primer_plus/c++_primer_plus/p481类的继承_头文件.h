// 程序清单 13.1 程序清单 13.4
// 派生类构造函数在初始化基类私有数据的时候用的是成员初始化列表语法
// 派生类不继承基类的构造函数, 所以将构造函数生成虚函数也没什么意义
#ifndef TABTENN0_H_
#define TABTENN0_H_
#include <string>
using std::string;

// 一个简单的基类
class TableTennisPlayer
{
private:
	string firstname;
	string lastname;
	bool hasTable;
public:
	TableTennisPlayer(const string & fn = "none", const string & ln = "none", bool ht = false);
	void Name() const;  // 这里的const的意思是引用他的对象是不能被改变的
	bool HasTable() const {return hasTable;}
	void ResetTable(bool v){hasTable = v;}
};

// 程序清单 13.4
class RatedPlayer : public TableTennisPlayer  
{  // : 指出后面是基类 public指出是公有派生(基类的公有成员成为派生类的公有成员, 基类的私有成员成为派生类的一部分, 但是只能通过公有或保护方法访问)
private:
	unsigned int rating;
public:
	// 派生类的构造函数必须为基类的成员提供数据
	RatedPlayer(unsigned int r = 0, const string & fn = "none", const string & ln = "none", bool ht = false);
	RatedPlayer(unsigned int r, const TableTennisPlayer & tp);
	unsigned int Rating() const {return rating;}
	void RestRating(unsigned int r){rating = r;}
};
#endif