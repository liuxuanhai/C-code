						// 关于继承的学习  然后下节是多态继承

// 派生类不集成基类的构造函数, 所以将构造函数设置成虚函数没什么意义
// 公有继承: is-a关系

#ifndef 会员管理_H_
#define 会员管理_H_

#include <string>
using std::string;
class TableTennisPlayer
{
private:
	string	strFirstName;
	string	strLastName;
	bool	isHasTable;
public:
	TableTennisPlayer(const string & fn = "FirstName", const string & ln = "LastName", bool ht = false);
	void ShowName() const;
	bool GetisHasTable() const { return isHasTable; }
	void ResetTable(bool v) { isHasTable = v; }
};

class RatedPlayer : public TableTennisPlayer	// 公有派生: 公有->公有 私有->成为派生类的一部分, 但是只能通过基类的公有和保护方法访问
												// 派生类不继承基类的构造函数
{
private:
	unsigned int rating;
public:
	RatedPlayer(unsigned int r = 0, const string & fn = "fname", const string & ln = "lname", bool ht = false);
	RatedPlayer(unsigned int r, const TableTennisPlayer & tp);	// 派生类的构造函数必须给派生的新成员和基类的成员提供数据;
						// 由于多态, tp也能是派生类				// 派生类的构造函数必须使用基类的构造函数(如果没有显式调用将会隐式调用默认构造函数);
																// 创建派生类对象的时候, 程序首先创建基类对象, 这意味着基类对象应该在进入派生类构造函数之前被创建, C++使用成员初始化列表语法完成这种工作;
																// 释放对象的顺序与创建的顺序相反, 先调用派生类对象的析构函数, 然后调用基类的析构函数;
	unsigned int GetRating() const { return rating; }
	void ResetRating(unsigned int r) { rating = r; }
};

#endif