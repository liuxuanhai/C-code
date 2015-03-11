#ifndef 程序清单14_17
#define 程序清单14_17
#include <iostream>
#include <cstdlib>
				// 表达式参数只能是整型, 枚举, 引用, 指针, 所以double n是错的, 但是double * n是对的.
template <class T, int n>  // 模板代码不能修改参数的值, 也不能使用参数的地址, 所以不能使用n++或&n等表达式, 实例化模板的时候表达式参数的值必须是常量表达式
class ArrayTP
{
private:
	T ar[n];
public:
	ArrayTP() {}
	explicit ArrayTP(const T & v);  // 将每个元素都初始化为形参的数值
	virtual T & operator[](int i);
	virtual T operator[](int i) const;
};

template <class T, int n>
ArrayTP<T, n>::ArrayTP(const T & v)
{
	for (int i = 0; i < n; i++)
		ar[i] = v;
}

template <class T, int n>
T & ArrayTP<T, n>::operator[](int i)
{
	if (i < 0 || i >= n)
	{
		std::cerr << "Error in array limits: " << i << " is out of range\n";
		std::exit(EXIT_FAILURE);
	}
	return ar[i];
}

template <class T, int n>
T ArrayTP<T, n>::operator[](int i) const
{
	if (i < 0 || i >= n)
	{
		std::cerr << "Error in array limits: " << i << " is out of range\n";
		std::exit(EXIT_FAILURE);
	}
	return ar[i];
}

#endif