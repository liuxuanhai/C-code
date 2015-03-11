// ±‡≥Ã¡∑œ∞ 6.11 (3)
#include <iostream>
int main()
{
	using namespace std;
	char ch = 'q';
	
	cout << "Please enter one of the follwing choice: \n";
	cout << "c) carnivore         p) pianist\n";
	cout << "t) tree              g) game\n";
	while (EOF != (ch = cin.get()))
	{
		while (cin.get() != '\n')
				continue;
		switch (ch)
		{
		case 'c' : cout << "carnivore\n"; break;
		case 'p' : cout << "pianist\n"; break;
		case 't' : cout << "tree\n"; break;
		case 'g' : cout << "game\n"; break;
		default  : cout << "Bad input! Again: "; continue; break;
		}
		cout << "Please enter one of the follwing choice: \n";
		cout << "c) carnivore         p) pianist\n";
		cout << "t) tree              g) game\n";
	}

	return 0;
}