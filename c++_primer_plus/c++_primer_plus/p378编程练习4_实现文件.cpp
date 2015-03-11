// 程序清单 10.10 (4) 实现文件
#include <iostream>
#include "p378编程练习4.h"

namespace SALES
{
	using std::cin;
	using std::cout;
	using std::endl;
	Sales::Sales(const double ar[], int n)
	{
		if (n < 0)
			n = 0;
		int limit = n < QUARTERS ? n : QUARTERS;
		double total = 0;
		min = 0;
		max = 0;
		average = 0;
		if (limit > 0)
			min = max = ar[0];
		int i;
		for (i = 0; i < limit; i++)
		{
			sales[i] = ar[i];
			total += ar[i];
			if (ar[i] > max)
				max = ar[i];
			else if (ar[i] < min)
				min = ar[i];
		}
		for (i = limit; i < QUARTERS; i++)
			sales[i] = 0;
		if (limit > 0)
			average = total / limit;
	}

	Sales::Sales()
	{
		min = 0;
		max = 0;
		average = 0;
		for (int i = 0; i < QUARTERS; i++)
			sales[i] = 0;
	}

	void Sales::setSales()
	{
		double sa[QUARTERS];
		int i;
		for (i = 0; i < QUARTERS; i++)
		{
			cout << "Enter sales for quarter " << i + 1 << ": ";
			cin >> sa[i];
		}

		// create temporary object, copy to invoking object
		*this = Sales(sa, QUARTERS);
	}

	void Sales::showSales()
	{
		cout << "Sales:\n";
		for (int i = 0; i < QUARTERS; i++)
			cout << "Quarter " << i + 1 << ": $"
			<< sales[i] << endl;
		cout << "Average: $" << average << endl;
		cout << "Minimum: $" << min << endl;
		cout << "Maximum: $" << max << endl;
	}
}