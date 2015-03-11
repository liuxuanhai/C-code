#include <iostream>
#include <string>
#include <stdexcept>
class bad_hmean : public std::logic_error
{
public:
	bad_hmean(std::string str = "Bad_hmean: 错误") : logic_error(str) {}
};

class bad_gmean : public std::logic_error
{
public:
	bad_gmean(std::string str = "Bad_Gmean: 错误类型") : logic_error(str) {}
};

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
		catch (bad_hmean & bg)
		{
			cout << bg.logic_error::what();
			cout << "Try again.\n";
			continue;
		}
		catch (bad_gmean & hg)
		{
			cout << hg.logic_error::what();
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
		throw bad_hmean("hmean(): 数组越界\n");
	return 2.0 * a * b / (a + b);
}

double gmean(double a, double b)
{
	if (a < 0 || b < 0)
		throw bad_gmean("gmean(): 数组越界\n");
	return std::sqrt(a * b);
}