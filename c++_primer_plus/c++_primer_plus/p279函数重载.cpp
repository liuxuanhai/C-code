// 程序清单 8.10
#include <iostream>
unsigned long left(unsigned long num, unsigned ct);
char * left(const char * str, int n = 1);

int main()
{
	using namespace std;
	char * trip = "Hawaii!!";
	unsigned long n = 12345678;
	int i;
	char * temp;

	for (i = 1; i < 12; i++)
	{
		cout << left(n, i) << endl;
		temp = left(trip, i);
		cout << temp << endl;
		delete [] temp;
	}

	return 0;
}

char * left(const char * str, int n)
{
	int i = 0;
	while (str[i++]);
	if (n < 0)
		n = 0;
	else if (n > i)
		n = i;     // 防止用户输入100000等不合理的数导致动态分配过多内存
	//std::cout << n << std::endl;
	char * p = new char[n + 1];
	for (i = 0; i < n; i++)
		p[i] = str[i];
	while (i <= n)
		p[i++] = '\0';

	return p;
}

unsigned long left(unsigned long num, unsigned ct)
{
	unsigned digits = 1;
	unsigned long n = num;
	if (ct == 0 || num == 0)
		return 0;
	while (n /= 10)
		digits++;
	if (digits > ct)
	{
		ct = digits - ct;
		while (ct--)
			num /= 10;
		return num;
	}
	else
		return num;
}