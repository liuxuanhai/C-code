// 创建: 2014-08-20 13:33:56
#include <iostream>
#include <list>
using namespace std;

int main()
{
	list<char> coll;

	// append elements  from 'a' to 'z'
	for (char c = 'a'; c <= 'z'; ++c)
		coll.push_back(c);

	// print all elements 
	// - iterator over all elements
	list<char>::const_iterator pos;	// 迭代器嵌套在了list<char>容器中
		// 这里声明的是一个"指向容器中的不可变元素"的迭代器

	for (pos = coll.begin(); pos != coll.end(); ++pos)	// 使用迭代器
		cout << *pos << ' ';
	cout << endl;
}