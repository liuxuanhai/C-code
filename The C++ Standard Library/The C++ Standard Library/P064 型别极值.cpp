// 创建: 2014-08-20 08:48:20

// 实现的思想: template虽然是为所有型别一次性的撰写出一个通用的解决方案, 但是可以以template为每个型别提供共通的接口. 方法是: 不但提供通用的template, 还提供其特例化(specialization)版本, 特例化版本给出min(), max(), 非特例化的直接is_specialized = false;

#include <iostream>
#include <limits>	// for numeric_limits template
#include <string>
using namespace std;
// is_specialized 为false表示此型别没有极值, 为true说明有特例化的template版本提供极值
int main()
{
	// use textual representation for bool
	cout << boolalpha;

	// print maximum of integral types
	cout << "max(short): "	<< numeric_limits<short>::max() << endl;
	cout << "max(int): "	<< numeric_limits<int>::max() << endl;
	cout << "max(long): "	<< numeric_limits<long>::max() << endl;
	cout << endl;

	// print maximum of floating-point types
	cout << "max(float): " << numeric_limits<float>::max() << endl;
	cout << "max(double): "<< numeric_limits<double>::max() << endl;
	cout << "max(long double): "	<< numeric_limits<long double>::max() << endl;
	cout << endl;

	// print whether char is signed
	cout << "is_signed(char): " << numeric_limits<char>::is_signed << endl;
	cout << endl;

	// print whether numeric limits for type string exit
	cout << "is_specialized(string): " << numeric_limits<string>::is_specialized << endl;
}