// 建立于 2013.12.13.19
// 复习:  2014.08.14.21  # 1

// 异常传递对象的好处: # 1
	// 1.	可以使用不同的异常类型来区分不同的函数在不同的情况下引发的异常;
	// 2.	对象可以携带信息, 程序员可以根据这些信息来确定引发异常的原因, 同时, catch块可以根据这些异常来决定采取什么样的措施;

// 程序清单 15.10 + 15.11
#include <iostream>
class bad_hmean
{
private:
	double v1;
	double v2;
public:
	bad_hmean(double a = 0, double b = 0) : v1(a), v2(b) {}
	void mesg();
};

inline void bad_hmean::mesg()
{
	std::cout << "hmean(" << v1 << ", " << v2 << "): "
		<< "invalid arguments: a = -b\n";
}

class bad_gmean
{
public:
	double v1;
	double v2;
	bad_gmean(double a = 0, double b = 0) : v1(a), v2(b) {}
	const char * mesg();
};

inline const char * bad_gmean::mesg()
{
	return "gmean() arguments should be >= 0\n";
}

#include <cmath>
double hmean(double a, double b);
double gmean(double a, double b);
int main(void)
{
	using std::cout;
	using std::endl;
	using std::cin;

	double x, y, z;

	cout << "Enter two numbers: ";
	while (cin >> x >> y)
	{
		try
		{
			z = hmean(x, y);
			cout << "Harmonic mean of " << x << " and " << y << " is " << z << endl;
			cout << "Geometric mean of " << x << " and " << y << " is " << gmean(x, y) << endl;
			cout << "Enter next set to numbers <q to qiut>: ";
		}
		catch (bad_hmean & bg)	// 这里使用的是引用, 注意变量的存在期限 # 1
								// 引发异常的时候, 编译器总是创建一个临时拷贝, 即使异常规范和catch块中指定的是引用 # 1
								// 这里的bg是对hmean()中创建的自动变量(throw bad_hmean(a, b);)的一个临时拷贝的引用, 当hmean()函数执行完成以后, throw创建的自动变量将不复存在, 然而这里引用的是副本, 所以不会出现错误 # 1
								// 但是这里为什么还是用引用呢, 反正都是生成一个副本, 直接使用传值不就得了, 反正引用避免创建副本的效率已经不存在了.  原因是: 引用还有另外一个特征, 基类引用可以指向派生类 # 1
								// 可以创建捕获对象而不是引用的处理程序, 在catch语句中使用基类对象时, 将捕获所有的派生类对象, 但是派生特性将会被剥去, 因此将使用虚方法的积累版本 # 1
		{
			bg.mesg();
			cout << "Try again.\n";
			continue;
		}
		catch (bad_gmean & hg)
		{
			cout << hg.mesg();
			cout << "Value used: " << hg.v1 << ", " << hg.v2 << endl;
			cout << "Sorry, you don't get to play any more.\n";
			break;
		}
	}
	cout << "Bye!\n";

	return 0;
}

double hmean(double a, double b)
{
	if (a == -b)
		throw bad_hmean(a, b);
	return 2.0 * a * b / (a + b);
}

double gmean(double a, double b)
{
	if (a < 0 || b < 0)
		throw bad_gmean(a, b);
	return std::sqrt(a * b);
}