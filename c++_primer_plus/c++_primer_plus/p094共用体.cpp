// c primer plus中称之为联合
// 由于共用体每次只能存储一个值, 因此他必须有足够的空间来储存最大的成员值, 所以, 共用体的长度为其最大成员的长度;
// 共用体的用途之一是, 当数据项实用两种或者更多的格式的时候(但是不会同时使用), 可以节省空间;
#include <iostream>
using namespace std;
int main(void)
{
	union one4all
	{
		int int_val;
		long long_val;
		double double_val;
	};
	one4all pail;
	pail.int_val = 15;  // store an int
	cout << pail.int_val << endl;
	cout << pail.long_val << endl;  // 即使这里写成了long_val我们之前也没有给她赋值, 他一样输出15
	pail.double_val = 1.38;  // store an double
	cout << pail.double_val << endl;

	return 0;
}