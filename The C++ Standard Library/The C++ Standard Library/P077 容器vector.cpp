// 创建: 2014-08-20 11:27:42
#include <iostream>
#include <vector>
using namespace std;

int main()
{
	vector<int> coll;

	// append elements with values 1 to 6
	for (int i = 0; i < 6; i++)
		coll.push_back(i);
	// print all elements followed by a space
	for (decltype(coll.size()) i = 0; i < coll.size(); ++i)	// coll.size 返回类型是size_t, 是无符号整型 decltype(expression) expression只是用于推断类型, 并不会真正执行这个表达式
		cout << coll[i] << ' ';
	cout << endl;
}