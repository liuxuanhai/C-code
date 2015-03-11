// 创建: 2014-08-21 09:21:00
// 1.	通常, 必须设定第一个区间的起点和终点, 其他区间只需设定起点, 终点可由第一区间的元素数量判断出来
// 2.	必须确保第二(以及其他)区间所拥有的元素数量至少和第一区间的元素个数相同
// 3.	关联式容器不可能当作覆写算法的操作目标
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
using namespace std;
int main()
{
	list<int>		coll1;
	vector<int>		coll2;

	// insert elements from 1 to 9
	for (int i = 0; i <= 9; ++i)
		coll1.push_back(i);
	// RUNTIME ERROR:
	// - overwrites nonexisting elements in the destination
	// - Expression: vector iterator not dereferencable
	//copy(coll1.begin(), coll1.end(), coll2.begin());	// 将第一区间的元素全部拷贝到目标区间
		// 这里是覆写动作(overwrites)而非安插操作(inserts)
		// 如果足够幸运, 覆写coll2.end()后边的东西会使程序立即崩溃 -- 起码知道错了. 当然, 可以使用STL安全版本强制自己获得这种幸运

	coll2.resize(coll1.size());
	copy(coll1.begin(), coll1.end(), coll2.begin());
	if (equal(coll1.begin(), coll1.end(), coll2.begin()))
		for (auto pos = coll2.begin(); pos != coll2.end(); ++pos)
			cout << *pos << ' ';
	cout << endl;

	deque<int> coll3(coll1.size());
	copy(coll1.begin(), coll1.end(), coll3.begin());
	if (equal(coll3.begin(), coll3.end() - 4, coll1.begin()))	// coll1的是双向迭代器, 不能 - 4运算
		for (auto pos = coll3.begin(); pos != coll3.end(); ++pos)
			cout << *pos << ' ';
	cout << endl;

	if (!equal(coll3.begin(), coll3.end(), coll2.begin() + 4))
		cout << "equal中目标区间可以比源区间少??" << endl;
}