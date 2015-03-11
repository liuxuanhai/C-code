// 创建: 2014-08-21 16:32:39

// 算法与成员函数的比较, 比如: list中使用remove算法, 此时使用者肯定是个逗逼, 因为remove在移除list中的元素的时候, 会让后边的元素覆盖前边的, 喔艹, list最好的常数时间复杂度的删除优势荡然无存了...
// 在这种更易型算法表现很差劲的容器中, 会提供相应的成员函数,比如: list::remove()...
#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
using namespace std;

int main()
{
	list<int> coll;
	// insert elements from 6 to 1 and 1 to 6
	for (int i = 0; i < 6; i++)
	{
		coll.push_front(i);
		coll.push_back(i);
	}
	// remove all elements with value 3
	// - poor performace
	coll.erase(remove(coll.begin(), coll.end(), 3), coll.end());

	copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	// remove all elements with value 4
	// - good performance
	coll.remove(4);
	copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
}