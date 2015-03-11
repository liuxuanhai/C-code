// 程序清单 8.8 (2)
#include <iostream>
#include <string>
struct CandyBar
{
	std::string Name;
	double weight;
	int power;
};

void add(CandyBar &, char * = "Millennium Munch", double = 2.85, int = 350);
void show(const CandyBar &);

int main()
{
	CandyBar b1, b2;
	add(b1);
	add(b2, "daxionggege", 3.33, 333);
	show(b1);
	show(b2);

	return 0;
}

void add(CandyBar & stru, char * str, double dou, int in)
{
	stru.Name = str;  // string = 指针可以?????? 居然可以!!
	stru.weight = dou;
	stru.power = in;
}

void show(const CandyBar & stru)
{
	using namespace std;
	cout << "Name:\t" << stru.Name << endl;
	cout << "Weight:\t" << stru.weight << endl;
	cout << "Power:\t" << stru.power << endl;
}