// 创建: 2014-08-21 12:49:37
// 配接器: C++标准程序库预先定义的特殊迭代器
// 安插型迭代器: 将算法的覆写方式改成了安插, 解决了"目标空间不足"的问题, 一共有三种安插式迭代器;

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <algorithm>
#include <iterator>	// back_inserter()的头文件
using namespace std;

int main()
{
	list<int> coll1;

	for (int i = 0; i <= 9; ++i)
		coll1.push_back(i);

	// copy the elements of coll1 into coll2 by appending them
	vector<int> coll2;
	copy(coll1.begin(), coll1.end(), back_inserter(coll2));		// 安插于容器!最尾端!	内部调用push_back(), 在容器尾端插入元素(此即"追加"动作), 只有在提供了push_back()成员函数的容器中, 这个才能派上用场(vector, deque, list)
	for (auto pos = coll2.begin(); pos != coll2.end(); ++pos)
		cout << *pos << " ";
	cout << endl;

	// copy the elements of coll1 into coll3 by inserting them at the front - reverses the order of the elements
	deque<int> coll3;
	copy(coll1.begin(), coll1.end(), front_inserter(coll3));	// 安插于容器最前端, 这种动作逆转了被安插的元素次序, 只能在提供了push_front()成员函数的容器中使用(deque, list)
	for (auto pos = coll3.begin(); pos != coll3.end(); ++pos)
		cout << *pos << " ";
	cout << endl;

	// copy elements of coll1 into coll4
	// - only inserter that works for associative collections
	set<int> coll4;
	copy(coll1.begin(), coll1.end(), inserter(coll4, coll4.begin()));	// 一般性安插器, 将元素插入"初始化时接受之第二参数"所指位置的前方, 内部调用insert(), 以新值新位置作为参数, 所有STL容器都提供了insert()参数, 这个是唯一可用于关联式容器身上的一种预先定义好的inserter
		// 虽然在关联式容器中不能指定其位置, 这里给的位置就是只是一个提示了, 帮助他们确定从什么地方开始搜寻正确的安插位置, 如果提示的不正确, 效率上的表现会比"没有提示"更糟糕
	for (auto pos = coll4.begin(); pos != coll4.end(); ++pos)
		cout << *pos << " ";
	cout << endl;

	copy(coll4.begin(), coll4.end(), inserter(coll2, coll2.begin() + 5));
	for (auto pos = coll2.begin(); pos != coll2.end(); ++pos)
		cout << *pos << " ";
	cout << endl;
}