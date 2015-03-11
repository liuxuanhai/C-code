// 创建: 2014-08-20 12:59:40
// list由双向链表实作而成, 不提供随机存取

#include <iostream>
#include <list>
using namespace std;

int main()
{
	list<char> coll;

	// append elements from 'a' to 'z'
	for (char c = 'a'; c <= 'z'; ++c)
		coll.push_back(c);
	// print all elements
	// - while there are elements
	// - print and remove the first element
	while (!coll.empty())
	{
		cout << coll.front() << ' ';
		coll.pop_front();	// 并不返回被删除的元素
	}
	cout << endl;
}