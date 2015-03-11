// 程序清单 8.9
#include <iostream>
const int ArSize = 80;
char * left(const char * str, int n = 1);  // 默认参数在原型中设置 他的定义与普通函数一样 ###注意: 默认参数的定义顺序是从右向左, 不能跳跃
int main()
{
	using namespace std;
	char sample[ArSize];
	cout << "Enter a string:\n";
	cin.get(sample, ArSize);
	char *ps = left(sample, 4);
	cout << ps << endl;
	delete [] ps;
	ps = left(sample);
	cout << ps << endl;
	delete [] ps;

	return 0;
}

char * left(const char * str, int n)
{
	if (n < 0)
		n = 0;
	char * p = new char[n + 1];
	int i;
	for (i = 0; i < n && str[i]; i++)
		p[i] = str[i];
	while (i <= n)
		p[i++] = '\0';
	
	return p;
}