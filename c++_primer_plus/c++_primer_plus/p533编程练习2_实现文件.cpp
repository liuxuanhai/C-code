#include "p532编程练习2_头文件.h"
#include <cstring>
#include <iostream>
using namespace std;
Cd::Cd(char * s1, char * s2, int n, double x)
{
	performers = new char[strlen(s1) + 1];
	strcpy(performers, s1);

	label = new char[strlen(s2) + 1];
	strcpy(label, s2);
	
	selections = n;
	playtime = x;
}

Cd::Cd(const Cd & d)
{
	performers = new char[strlen(d.performers) + 1];
	strcpy(performers, d.performers);

	label = new char[strlen(d.label) + 1];
	strcpy(label, d.label);

	playtime = d.playtime;
	selections = d.selections;
}

Cd::Cd()
{
	performers = nullptr;;
	label = nullptr;
    selections = 0;
    playtime = 0.0;
}

Cd::~Cd()
{
	delete [] performers;
	delete [] label;
}

Cd & Cd::operator= (const Cd & d)
{
	if (&d == this)
		return *this;

	delete [] performers;
	delete [] label;

	performers = new char[strlen(d.performers) + 1];
	strcpy(performers, d.performers);

	label = new char[strlen(d.label) + 1];
	strcpy(label, d.label);

	playtime = d.playtime;
	selections = d.selections;

	return *this;
}

void Cd::Report() const
{
	cout << "Performers:\n    " << performers << endl;
	cout << "Label:\n    " << label << endl;
	cout << "Selections:\n    " << selections << endl;
	cout << "Playtime:\n    " << playtime << endl;
}

Classic::Classic(char * bes, char * s1, char * s2, int n, double x) : Cd(s1, s2, n, x)
{
	best = new char[strlen(bes) + 1];
	strcpy(best, bes);
}

Classic::Classic()  // 会自动调用基类的默认构造函数
{
	best = nullptr;
}

Classic::~Classic()  // 会自动调用基类默认析构函数
{
	delete [] best;
}

void Classic::Report() const
{
	Cd::Report();
	cout << "Best: \n    " << best << endl;
}

Classic & Classic::operator=(const Classic & d)
{
	if (this == &d)
		return *this;

	Cd::operator=(d);
	delete [] best;
	best = new char[strlen(d.best) + 1];
	strcpy(best, d.best);

	return *this;
}