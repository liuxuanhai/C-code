// 创建: 2014-08-21 18:33:51
// 数值的上溢下溢和负数对应的正数都在下面图中展现了出来(0 - 7的范围图(3位))
//		-1  0  1    7  0  1
//      -2     2    6     2
//      -3 -4  3    5  4  3
//
//      011 + 001 = 100
//      3 + 1 = 4(unsigned Byte3)
//		3 + 1 = -4(Byte3)
//		转换: 8 - 4 = 4
#include <iostream>
#include <limits>
using namespace std;
void print(int t)
{
	printf("%11d => ", t);
	for (int i = 0; i < sizeof(int) * 8; i++)	
	{
		if (i % 4 == 0)
			cout << " ";
		cout << ((0x80000000 & t) >> 31);
		t <<= 1;
	}
	cout << endl;
}
int main()
{
	cout << "intMax     =  " << numeric_limits<int>::max() << endl;
	cout << "intMax + 1 = " << numeric_limits<int>::max() + 1 << endl;
	cout << "intMax + 2 = " << numeric_limits<int>::max() + 2 << endl << endl;
	
	cout << "-1(int) = " << unsigned(-1) << "(unsigned int)\n\n";

	print(numeric_limits<int>::max());
	print(numeric_limits<int>::max() + 1);
		// 这里说明 -2147483648内部是用1000 0000 0000 0000 0000 0000 0000 0000 表示的
	print(numeric_limits<int>::max() + 2);
	print(numeric_limits<int>::max() + 3);

	// 未初始化的变量内部存储的值
	print(-858993460);
}