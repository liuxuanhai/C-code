#include <iostream>
#define JDZ(x) ((x) > 0 ? (x) : (-x))
using namespace std;
int main(void)
{
	char ch;
	cout << "输入你的菱心大写字母: \n";
	cin >> ch;
	
	int X = ch - 'A';
	
	for (int y = -X; y <= X; y++, cout << '\n')
		for (int x = -X; x <= X; x++)
			if (JDZ(x) + JDZ(y) <= X)
				cout << char('A' + X - JDZ(x) - JDZ(y));
			else
				cout << ' ';

	return 0;
}