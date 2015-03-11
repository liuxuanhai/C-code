// 建立于 2013.12.13.19
// 复习:  2014.08.14.20  # 1
// C++异常: 对程序运行过程中异常状况的一种响应; # 1
// 异常处理: 程序员预防程序发生运行阶段错误的一个强大而灵活的工具, 它使得一个指定的运行阶段错误由不确定的结果在所有系统上都以相同的受控方式运行 # 1

#include <iostream>
#include <cstdlib>  // abort()

double hmean(double a, double b);

int main()
{
	double x, y, z;

	std::cout << "Enter two numbers: ";
	while (std::cin >> x >> y)
	{
		z = hmean(x, y);
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
	{
		std::cout << "untenable arguments to hmean()\n";
		std::abort();  // 这里直接终止程序, 不会先返回到main
	}
	return 2.0 * a * b / (a + b);
}