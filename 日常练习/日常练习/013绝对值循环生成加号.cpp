#include <iostream>
using namespace std;
int main(void)
{
	int a;
	
	cout << "Enter a number:\n";
	cin >> a;
	
	for (int y = -3 * a; y <= 3 * a; y++, cout << '\n')
	{
		for (int x = -3 * a; x <= 3 * a; x++)
		{
			if (
				((-3 * a <= x && x <= 3 * a)&&(-a <= y && y <= a)) || 
				((-3 * a <= y && y <= 3 * a)&&(-a <= x && x <= a))
				)
				cout << '*';
			else
				cout << ' ';
		}
	}

	return 0;
}