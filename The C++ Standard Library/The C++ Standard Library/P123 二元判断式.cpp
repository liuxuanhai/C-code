// ´´½¨: 2014-08-22 09:56:39
#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
using namespace std;

class Person
{
private: 
	string f;
	string l;
public:
	Person(const string & ff, const string & ll): f(ff), l(ll) {} 
	string firstname() const { return f; }
	string lastname() const	{ return l; }
};

// binary function predicate:
// - return whether a person is less than another person
bool personSortCriterion(const Person & p1, const Person & p2)
{
	return p1.firstname() < p2.firstname();	
}

int main()
{
	deque<Person> coll;
	char tmp[100];
	for (int i = 0; i < 10; i++)
		coll.push_back(Person(itoa(rand() % 100, tmp, 10), itoa(rand() % 100, tmp, 10)));
	for (auto pos = coll.begin(); pos != coll.end(); ++pos)
		cout << pos->firstname() << " - " << pos->lastname() << endl;
	cout << endl;
	sort(coll.begin(), coll.end(), personSortCriterion);
	for (auto pos = coll.begin(); pos != coll.end(); ++pos)
		cout << pos->firstname() << " - " << pos->lastname() << endl;
}