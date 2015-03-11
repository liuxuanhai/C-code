// 创建: 2014-08-21 16:17:07
// 关联式容器的元素值与位置的特殊性不允许更易型算法更改元素值, 更不允许删除元素

#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>
using namespace std;

int main()
{
	set<int> coll;
	// insert elements from 1 to 9
	for (int i = 1; i < 10; ++i)
		coll.insert(i);
	// print all elements of the collection
	copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	// remove all elements with value 3
	// - algorithm remove() does not work
	// - instead member function erase() works
	int num = coll.erase(3);	// 返回从coll中移除的元素值为3的元素个数

	copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	// print number of removed elements
	cout << "number of removed elements: " << num << endl;
}