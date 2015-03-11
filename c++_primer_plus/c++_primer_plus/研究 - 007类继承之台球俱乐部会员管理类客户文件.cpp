#include <iostream>
#include "007研究 - 类继承之台球俱乐部会员管理类.h"

int main(void)
{
		// 基类测试

	//using std::cout;
	//TableTennisPlayer P1("He", "Shixiong", true);	// 这里声明构造函数的时候使用的是const string &, 这里写入的是"He"(const char *),
	//												// const 引用可以生成临时变量, 所以, 这里会自动调用string的转换构造函数, 将C-风格字符串转化为string对象
	//												// 然后这里将是对临时变量的引用;
	//TableTennisPlayer P2("Hello", "C++", false);
	//P1.ShowName();
	//if (P1.GetisHasTable())
	//	cout << " : has a table.\n";
	//else
	//	cout << " : hasn't a table.\n";
	//P2.ShowName();
	//if (P2.GetisHasTable())
	//	cout << " : has a table.\n";
	//else
	//	cout << " : hasn't a table.\n";

		// 派生类测试

	using std::cout;
	using std::endl;
	TableTennisPlayer P1("TableTennisPlayer", "Base", false);
	RatedPlayer P2(1140, "RatedPlayer", "Derive", true);

	P2.ShowName();
	if (P2.GetisHasTable())
		cout << " : has a table.\n";
	else
		cout << " : hasn't a table.\n";

	P1.ShowName();
	if (P1.GetisHasTable())
		cout << " : has a table.\n";
	else
		cout << " : hasn't a table.\n";

	cout << "Name : ";
	P2.ShowName();
	cout << "; " << P2.GetRating() << endl;

	RatedPlayer P3(1212, P1);
	cout << "Name : ";
	P3.ShowName();
	cout << "; " << P3.GetRating() << endl;

	RatedPlayer P4(20140511, P3);	// 这里涉及到了类之间的多态, 这里P3是一个派生类, 但是用在了TablePlayer(TablePlayer &)中;
	cout << "Name : ";
	P4.ShowName();
	cout << "; " << P4.GetRating() << endl;

	return 0;
}