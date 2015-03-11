// 自己总结
#include <iostream>
using namespace std;

template<typename T> auto add(const T a, T b) -> decltype (a + b)
{
	return a + b;
}

template<class T1, class T2> auto jian(T1 a, T2 b) ->decltype (a - b)
{
	return a - b;
}

template<class R1, typename R2> auto cheng(R1 &a, R2 &b) ->decltype (a * b)
{
	typedef decltype (a) tya;  // 如果是double &a的话那么tya 代表double &    ???
	typedef decltype ((b)) tyb;// 如果是double &b的话那么tyb 代表double &&   ???
	tya aa = a;
	tyb bb = b;
	cout << "aa: " << aa << endl;
	cout << "bb: " << bb << endl;
	cout << "aa + bb : " << aa + bb << endl;

	return a * b;
}

int main()
{
	int a = 6;
	double b = 2.2;

	cout << add(double(a), b) << endl;  // 为什么这里直接写a不能进行隐式的类型转换??????因为整数不能进行强制的类型转换(p290) 看下面
	cout << add<double>(a, b) << endl;  // 可以这样进行显示的实例化
	cout << jian(b, a) << endl;
	cout << jian(a, b) << endl;
	cout << cheng(a, b) << endl;

	return 0;
}