// 建立	2013.12.13.19
// 复习	2014.08.14.20  # 1

// 通过函数的返回值来判断问题
#include <iostream>
#include <cfloat>  // for DBL_MAX

bool hmean(double a, double b, double * ans);

int main()
{
	double x, y, z;

	std::cout << "Enter two numbers: ";
	while (std::cin >> x >> y)
	{
		if (hmean(x, y, &z))
			std::cout << "Harmonic mean of " << x << " and " << y
			<< " is " << z << std::endl;
		else
			std::cout << "One value should not be the negative "
				<< "of the other - try again.\n";
		std::cout << "Enter next set of numbers <q to qiut>: ";
	}
	std::cout << "Bye!\n";

	return 0;
}

bool hmean(double a, double b, double * ans)
{
	if (a == -b)
	{
		*ans = DBL_MAX;
		return false;
	}
	else
	{
		*ans = 2.0 * a * b / (a + b);
		return true;
	}
}