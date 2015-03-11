// 编程练习 10.10 实现文件
#include "p377编程练习2.h"
#include <iostream>
#include <cstring>
using namespace std;
Person::Person(const string & ln, const char * fn)
{
	strncpy(fname, fn, 24);
	fname[24] = '\0';
	lname = ln;
}
void Person::Show() const
{
	cout << fname << " " << lname << endl;
}
void Person::FormalShow() const
{
	cout << lname << ", " << fname << endl;
}