// 程序清单 3.8
// float 和 double 类型以及他们在表示数字时精度上的差异(即有效位数)
// 有效位是指数字中有意义的位, 如31564有效位有5个, 32000有效位有2个, 因为经过四舍五入精确到了千位, 后面的三个零仅仅相当于占位符
// c++保证float的有效位至少为32, 精度有效位至少为6, double的有效位至少为48, 精度有效位至少为15
// c++保证float double long double指数的范围至少是-37 ~ +37
#include <iostream>
int main()
{
	using namespace std;
	cout.setf(ios_base::fixed, ios_base::floatfield);
	// 通常cout会删除结尾的零, 例如: 将3333333.250000显示为3333333.25
	// 调用cout.stef()将会覆盖这种行为
	float tub = 10.0 / 3.0;
	double mint = 10.0 / 3.0;
	const float million = 1.0e6;

	cout << "tub = " << tub;
	cout << ", a million tubs = " << million * tub;
	cout << ",  \nand ten million tubs = ";
	cout << 10 * million * tub << endl;

	cout << "mint = " << mint << " and a million mint * 10000000000 = ";
	cout << million * mint * 10000000000 <<endl;  // 这里有16个3, 保证了在15位以上
	cout << sizeof(float);
	return 0;
}