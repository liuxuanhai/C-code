// 建立于 2013.12.13.19
// 复习:  2014.08.14.21  # 1

#include <iostream>
double hmean(double a, double b);
int main()
{
	double x, y, z;

	std::cout << "Enter two numbers: ";
	while (std::cin >> x >> y)
	{
		try   // 标示可能引发异常的代码块, 后面跟一个或多个catch
		{
			z = hmean(x, y);
		}
		// const char * s表名该异常处理程序与字符串异常相匹配 如果没有匹配的默认就会调用abort();
		catch (const char * s)  // catch 块对异常进行处理
		{
			std::cout << s << std::endl;
			std::cout << "Enter a new pair of numbers: ";
			continue;
		}

		// 如果函数引发了异常, 而没有try块或没有匹配的处理程序, 默认情况下会调用abort()函数, 但是可以修改这种行为 # 1

		std::cout << "Harmonic mean of " << x << " and " << y
			<< " is " << z << std::endl;
		std::cout << "Enter next set of numbers <q to qiut>: ";
	}
	std::cout << "Bye!\n";

	return 0;
}

double hmean(double a, double b)
{
	if (a == -b)
		throw "bad hmean() arguments: a = -b not allowed";  // 引发的异常是可以是字符串或者其他c++类型, 通常是类类型
	// throw语句类似于return语句, 因为他也终止函数的执行, 但是throw不是将控制权交给调用函数, 而是导致程序沿着函数调用序列后退, 直道找到包含try块的函数, 如果一直到了顶级的main函数仍然一次都没匹配过, 就会都调用abort函数, 当然, 这种默认行为是可以改变的
	return 2.0 * a * b / (a + b);
}