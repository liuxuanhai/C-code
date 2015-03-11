// ´´½¨: 2014-08-20 15:34:08
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	vector<int> coll;
	vector<int>::iterator pos;

	// insert elements from 1 to 6 in arbitrary order
	coll.push_back(2);
	coll.push_back(5);
	coll.push_back(4);
	coll.push_back(1);
	coll.push_back(6);
	coll.push_back(3);
	// find and print minimum and maximum elements
	pos = min_element(coll.begin(), coll.end());
	cout << "min: " << *pos << endl;
	pos = max_element(coll.begin(), coll.end());
	cout << "max: " << *pos << endl;
	// sort all elements
	sort(coll.begin(), coll.end());
	for (vector<int>::const_iterator pos = coll.begin(); pos != coll.end(); ++pos)
		cout << *pos << " ";
	cout << endl;
	// find the first element with value 3
	pos = find(coll.begin(), coll.end(), 3);
	cout << *pos << endl;
	// reverse the order of the found element with value 3 and all folling elements
	reverse(pos, coll.end());
	for (vector<int>::const_iterator pos = coll.begin(); pos != coll.end(); ++pos)
		cout << *pos << " ";
	cout << endl;
}