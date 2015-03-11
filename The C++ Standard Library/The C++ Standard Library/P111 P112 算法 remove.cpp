// 创建: 2014-08-21 14:31:25
// 为什么remove()不能删除元素只能通过将后边的元素覆盖前边元素来实现移除:
//		这是STL为了获取灵活性而付出的代价, 透过"以迭代器为接口", STL将数据结构和算法分离开来, 然而, 迭代器只不过是"容器中的某一位置"的抽象概念, 一般来说, 迭代器对自己所属的容器一无所知, 任何"以迭代器"访问容器元素的算法, 都无法透过迭代器调用容器类别提供的任何成员函数...(这里是erase())
#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
using namespace std;
#define Version 2
int main()
{
	list<int> coll;

	// insert elements from 6 to 1 and  1 to 6
	for (int i = 1; i <= 6; ++i)
	{
		coll.push_front(i);
		coll.push_back(i);
	}

	// print all elements of the collection
	cout << "Pre:  ";
	copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
#if Version == 1
	// remove all elements with value 3
	remove(coll.begin(), coll.end(), 3);	// 没有改变群集中元素数量, 多出来的5 6是未被覆盖的元素, 但是逻辑上他们已经不是这个群集的了
	// print all elements of the collection
	cout << "Post: ";
	copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
#elif Version == 2
	list<int>::iterator end = remove(coll.begin(), coll.end(), 3);	// 返回的就是新的逻辑上的结尾
	cout << "Post: ";
	copy(coll.begin(), end, ostream_iterator<int>(cout, " "));
	cout << endl;
	// print number of resulting elements
	cout << "number of removed elements: " << distance(end, coll.end()) << endl;
	// remove "removed" elements
	coll.erase(end, coll.end());
	// print all elements of the modified collection
	cout << "Post: ";
	copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
#endif
	
}