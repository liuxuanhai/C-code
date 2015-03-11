// 创建: 2014-08-20 16:16:05
// 半开区间: [begin, end)
#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

int main()
{
	list<int> coll;
	list<int>::iterator pos;

	// insert elements from 20 to 40
	for (int i = 20; i <= 40; ++i)
		coll.push_back(i);

	// find position of element with value 3
	// - there is none, so pos gets coll.end()
	auto a = coll.end();	// [ptr] = 0x004a95d8 {-842150451}
	pos = find(coll.begin(), coll.end(), 3);	// pos == coll.end!!!
	// cout << *pos << endl;	// Expression: list iterator not derefrencable
	// pos: [ptr] = 0x00000008 {???} => [ptr] = 0x004a95d8 {-842150451}(coll.end())
	if (pos == coll.end())
		cout << "3 不在coll中\n";

	// reverse the order of elements between found element and the end
	// - because pos is coll.end() it reverses an empty range
	reverse(pos, coll.end());	// 空范围

	// find positions of values 25 and 35
	list<int>::iterator pos25, pos35;
	pos25 = find(coll.begin(), coll.end(), 25);
	pos35 = find(coll.begin(), coll.end(), 35);

	// print the maximum of the corresponding range
	// - note: including pos25 but excluding pos 35
	cout << "max: " << *max_element(pos25, pos35) << endl;

	// process the elements including the last position
	cout << "max: " << *max_element(pos25, ++pos35) << endl;
}