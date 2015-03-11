// 创建: 2014-08-20 11:40:19
// deque(double-ended queue的缩写), 双队列, 双端队列, 可以向两端发展, 因此不论在尾部或头部安插元素都十分迅速, 在中间安插元素比较费时

#include <iostream>
#include <deque>
#include <vector>
using namespace std;

int main()
{
	deque<float> coll;

	// insert elements from 1.1 to 6.6 each at the front
	for (int i = 0; i <= 6; ++i)
		coll.push_front(i * 1.1);
	// print all elements followed by a space
	for (decltype(coll.size()) i = 0; i < coll.size(); ++i)
		cout << coll[i] << " ";
	cout << endl;

	vector<int> v;
	// v.push_front(1);	// vector没有给出push_front()成员函数....
		// 通常, STL容器只提供具备良好时间效能的成员函数, 这可以防止程序员调用性能很差的函数;
}