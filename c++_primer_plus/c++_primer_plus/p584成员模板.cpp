#define 模板内定义
#ifndef 模板内定义

#include <iostream>

using std::cout;
using std::endl;

template <typename T>
class Beta
{
private:
	template <typename V>
	class Hold
	{
	private:
		V val;
	public:
		Hold(V v = 0) : val(v) {}
		void show() const {cout << val << endl;}
		V getValue() const {return val;}
	};
	Hold<T> q;  // 模板对象
	Hold<int> n;  // 模板对象
public:
	Beta(T t, int i) : q(t), n(i) {}
	template<typename U>  // 模板方法
	U blab(U u, T t) {return (n.getValue() + q.getValue()) * u / t;}
	void show() const {q.show(); n.show();}
};

int main()
{
	Beta<double> guy(3.5, 3);
	cout << "T was set to double\n";
	guy.show();
	cout << "U was set to T, whitch is double, then U was set to int\n";
	cout << guy.blab(10, 2.3) << endl;
	cout << "U was set to int\n";
	cout << guy.blab(10.0, 2.3) << endl;
	cout << "U was set to double\n";
	cout << "Done\n";
	return 0;
}

#else

#include <iostream>

using std::cout;
using std::endl;

template<typename T>
class Beta
{
private:
	template<class V> class Hold;  // 声明类
	Hold<T> q;
	Hold<int> n;
public:
	Beta(T t, int i) : q(t), n(i) {}
	template<typename U>  // 模板方法
	U blab(U u, T t);// {return (n.getValue() + q.getValue()) * u / t;}
	void show() const {q.show(); n.show();}
};

// 定义类
template<typename T>
template<typename V>
class Beta<T>::Hold
{
private:
	V val;
public:
	Hold(V v = 0) : val(v) {}
	void show() const {std::cout << val << std::endl;}
	V getValue() const {return val;}
};

template<class T>
template<class U>
U Beta<T>::blab(U u, T t)
{
	return (n.getValue() + q.getValue()) * u / t;
}

int main()
{
	Beta<double> guy(3.5, 3);
	cout << "T was set to double\n";
	guy.show();
	cout << "U was set to T, whitch is double, then U was set to int\n";
	cout << guy.blab(10, 2.3) << endl;
	cout << "U was set to int\n";
	cout << guy.blab(10.0, 2.3) << endl;
	cout << "U was set to double\n";
	cout << "Done\n";
	return 0;
}

#endif