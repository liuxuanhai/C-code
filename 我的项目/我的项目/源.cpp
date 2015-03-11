#include <iostream>
using namespace std;

int main(void)
{
	// 1000 0100 0010 0001
	int a = 0x8421;
	cout << "a = " << a << endl;
	//for (int i = 0; i < 16; i++)
	{
		int a1 = 0x000f & a;
		a >>= 4;
		int a2 = 0x00f0 & a;
		a >>= 4;
		int a3 = 0x0f00 & a;
		a >>= 4;
		int a4 = 0xf000 & a;

		cout << a1 << endl
			<< a2 << endl
			<< a3 << endl
			<< a4 << endl;
	}

	return 0;
}