// 建立		2013.12.13.19
// 复习		2014.08.14.22  # 1

// 程序清单 15.10 和 15.12 # 1
#include <iostream>
class bad_hmean
{
private:
	double v1;
	double v2;
public:
	bad_hmean(double a = 0, double b = 0) : v1(a), v2(b) {}
	inline void mesg();
};

void bad_hmean::mesg()
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
	inline const char * mesg();
};

const char * bad_gmean::mesg()
{
	return "gmean() arguments should be >= 0\n";
}

#include <cmath>
#include <string>

class demo
{
private:
	std::string word;
public:
	demo (const std::string & str)
	{
		word = str;
		std::cout << "demo " << word << " created\n";
	}
	~demo()
	{
		std::cout << "demo " << word << " destroyed\n";
	}
	void show() const
	{
		std::cout << "demo " << word << " lives!\n";
	}
};

double hmean(double a, double b);
double gmean(double a, double b);
double means(double a, double b);

int main()
{
	using std::cout;
	using std::cin;
	using std::endl;

	double x, y, z;
	{
		demo d1("found in block in main()");
		cout << "Enter tow numbers: ";
		while (cin >> x >> y)
		{
			try
			{
				z = means(x, y);
				cout << "The mean mean of " << x << " and " << y
					<< " is " << z << endl;
				cout << "Enter next pair: ";
			}	// 如果一次没被处理, 在顶级的main()这里就只能调用abort()了, 但是这种行为可以改变 # 1
			catch (bad_hmean & bg)  // bg指向的是副本而不是本身, 因为函数执行完后其内的所有变量不复存在, 所以指向的是一个副本是好的, 这里还使用引用的原因是: 基类引用可以应用到派生类
			{
				bg.mesg();
				cout << "Try again.\n";
				continue;
			}
			catch (bad_gmean & hg)
			{
				cout << hg.mesg();
				cout << "Values used: " << hg.v1 << ", " << hg.v2 << endl;
				cout << "Sorry, you don't get to play anymore.\n";
				break;
			}
		}
		d1.show();
	}
	cout << "Bye.\n";
	cin.get();
	cin.get();
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

double means(double a, double b)
{
	double am, hm, gm;
	demo d2("found in means()");
	am = (a + b) / 2.0;
	try
	{
		hm = hmean(a, b);
		gm = gmean(a, b);  // 返回异常后只执行catch的内容
	}	// try块抛出的异常直接到了这里 # 1
	catch (bad_hmean & bg)
	{
		bg.mesg();
		std::cout << "Caught in means()\n";
		throw;  // 导致means()终止执行, 并将异常传递给他的调用函数main()函数 异常的抛出导致这里的自动变量(d2等)释放
			// 如果注释了, 那么这里会在执行完异常后将异常消息消除, 然后执行下边的d2.show(), 然后return到调用函数

	}	// 如果到了这里还没有匹配的异常(比如bad_gmean), 直接向上跳到调用函数main() # 1
	d2.show();
	return (hm + gm + am) / 3.0;
}