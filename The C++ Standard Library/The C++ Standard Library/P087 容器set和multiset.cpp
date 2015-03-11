// 创建: 2014-08-20 13:34:57

// 这里的multiset和set的用法一致
#include <iostream>
#include <set>
#include <algorithm>
#include <functional>	// for 仿函数std::greater<>
int main()
{
	// type of the collection
	//typedef std::set<int> IntSet;

	std::set<int> coll;

	// insert elements from  1 to 6 in arbitrary(任意的) order
	// - value1 gets inserted twice
	coll.insert(3);	// 新元素会根据排序规则自动安插到正确的位置
	coll.insert(1);
	coll.insert(5);
	coll.insert(4);
	coll.insert(1);	// repeat	// 这里重复的元素并没有成功添加进去
	coll.insert(6);
	coll.insert(2);

	// pirnt all elements
	// - iterate over all elements
	for (decltype(coll.cbegin()) pos = coll.begin(); pos != coll.end(); ++pos)
		std::cout << *pos << ' ';
	std::cout << std::endl;

	// 使用仿函数改变排序规则
	std::set<int, std::greater<int> > coll2;	// std::greater<int> 是一个仿函数
	for (decltype(coll.cbegin()) pos = coll.begin(); pos != coll.end(); ++pos)
		coll2.insert(*pos);
	for (decltype(coll2.cbegin()) pos = coll2.begin(); pos != coll2.end(); ++pos)
		std::cout << *pos << ' ';
	std::cout << std::endl;
}