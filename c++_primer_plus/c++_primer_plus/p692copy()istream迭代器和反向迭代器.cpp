#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

int main(void)
{
	using namespace std;

	int casts[10] = {6, 7, 2, 9, 4, 11, 8, 7, 10, 5};

	// STL sort()函数接受指向容器第一个元素的迭代器和指向超尾的迭代器
	// 指针满足所有迭代器的要求, 他支持随机访问(最高级迭代器的功能)
	cout << "对数组的内容进行升序排列: \n";
	sort(casts, casts + 10);
	for (auto x: casts)
		cout << x << " ";
	cout << endl;

	vector<int> dice(10);
	// capyfrom array to vector
	copy(casts, casts + 10, dice.begin());  // 迭代器是广义指针, 而指针满足所有迭代器要求, 迭代器是STL算法的接口, 而指针是迭代器, 因此STL算法可以使用指针来对局域指针的非STL容器进行操作, 例如, 可以将STL算法用于数组
	// copy()的前两个迭代器参数表示要复制的范围[), 最后一个迭代器表示要将第一个元素复制到什么位置, copy()函数将会覆盖目标中已有的数据, 同时目标容器必须足够大, 以便能容纳被复制的元素

	cout << "Let the dice be cast!\n";
	// creator an ostream iterator
	ostream_iterator<int, char> out_iter(cout, ", ");
	// int: 指出了被发送给输出流的数据类型
	// char: 指出了输入流使用的字符类型
	// cout: 指出了要使用的输出流, 也可以是用于文件的输出流
	// ", ": 在发送给输出流的每个数据项后显示的分隔符
	cout << "*(out_iter++) = 15: ";
	*(out_iter++) = 15;  // works like cout << 15 << ", ";
	// 对于常规指针, 这意味着将15赋给指针指向的位置, 然后将指针加1, 但是对于ostream_iterator, 这意味着将15和", "组成的字符串发送到cout管理的输出流中, 并为下一个输出操作做好了准备
	cout << endl;
	
	// copy from vector to output
	copy(dice.begin(), dice.end(), out_iter);  // 这意味着将dice容器的整个区间发送到输出流中, 即为显示容器的内存
	cout << endl;
	cout << "Implicit use of recerse iterator.\n";
	copy(dice.rbegin(), dice.rend(), out_iter);
	cout << endl;

	// 反向迭代器
	cout << "Explicit use of recerse iterator.\n";
	vector<int>::reverse_iterator ri;
	for (ri = dice.rbegin(); ri != dice.rend(); ++ri)
		cout << *ri << ' ';
	cout << endl;

	return 0;
}