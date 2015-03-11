#include "p531编程练习1_头文件.h"
#include <cstring>
#include <iostream>
using namespace std;
Cd::Cd(char * s1, char * s2, int n, double x)
{
	strncpy(performers, s1, 50);
	performers[49] = '\0';

	strncpy(label, s2, 20);
	performers[19] = '\0';

	selections = n;
	playtime = x;
}

Cd::Cd()
{
	performers[0] = '\0';
    label[0] = '\0';
    selections = 0;
    playtime = 0.0;
}

Cd::~Cd(){}

void Cd::Report() const
{
	cout << "Performers:\n    " << performers << endl;
	cout << "Label:\n    " << label << endl;
	cout << "Selections:\n    " << selections << endl;
	cout << "Playtime:\n    " << playtime << endl;
}

Classic::Classic(char * bes, char * s1, char * s2, int n, double x) : Cd(s1, s2, n, x)
{
	strncpy(best, bes, 100);
	best[99] = '\0';
}

Classic::Classic()  // 会自动调用基类的默认构造函数
{
	  best[0] = '\0';
}

//Classic::~Classic(){}

void Classic::Report() const
{
	Cd::Report();
	cout << "Best: \n    " << best << endl;
}