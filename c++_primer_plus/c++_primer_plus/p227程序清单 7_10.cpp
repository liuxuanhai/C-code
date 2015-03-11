// 程序清单 7.10
#include <iostream>
char * buildstr(char c, int n);
int main()
{
	using namespace std;
	int times;
	char ch;

	cout << "Enter a character: ";
	cin >> ch;
	cout << "Enter an integer: ";
	cin >> times;
	char *ps = buildstr(ch, times);
	cout << ps << endl;
	delete [] ps;
	cout << 1111;
	ps = buildstr('+', 20);
	cout << ps << " DONE " << ps << endl;
	delete [] ps;

	return 0;
}
char * buildstr(char c, int n)
{
	char * pstr = new char[n + 1];  // 注意 这里是[]而不是()!!!!!!!!!!!
	pstr[n] = '\0';
	while (n-- > 0)
		pstr[n] = c;
	return pstr;
}