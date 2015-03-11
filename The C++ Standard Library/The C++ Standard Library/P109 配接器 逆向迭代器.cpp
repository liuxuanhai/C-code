// 创建: 2014-08-21 14:14:43
// 逆向迭代器: 将递增运算转换成递减运算
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

int main()
{
	vector<int> coll;
	// insert elements from 1 to 9
	for (int i = 0; i <= 9; ++i)
		coll.push_back(i);
	// print all element in reverse order
	copy(coll.rbegin(), coll.rend(), ostream_iterator<int>(cout, " "));
		// rbegin()返回一个由coll定义的reverse iterator, 这个迭代器可作为"对群集coll的元素逆向遍历"的起点
		// rbegin()指向群集的结尾位置(也就是最后一个元素的位置)
		// rend()返回的reverse iterators他是一个"逾尾"位置, 只不过方向相反, 指的是容器内第一个元素的前一个位置

	cout << endl;
}