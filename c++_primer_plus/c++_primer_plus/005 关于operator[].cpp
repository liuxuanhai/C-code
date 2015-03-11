// 创建: 2014-08-21 20:43:32
// 实现classType a; a["string"] = value;
#include <iostream>
#include <string>
#include <iterator>
using namespace std;
class A
{
private:
	static const int SIZE = 10;
	int ar[SIZE];
public:
	A();
	void show(const string & prev = "", const string & next = "\n");
	int & operator[](const string & index);
};

A::A()
{
	for (int i = 0; i < SIZE; i++)
		ar[i] = i;
}

void A::show(const string & prev, const string & next)
{
	cout << prev;
	copy(ar, ar + SIZE, ostream_iterator<int>(cout, " "));
	cout << next;
}

int & A::operator[](const string & index)
{
	return ar[atoi(index.c_str())];
}

int main()
{
	A a;
	a.show();
	cout << a["0"];
	a["0"] = 4;
	a.show("\n");
}