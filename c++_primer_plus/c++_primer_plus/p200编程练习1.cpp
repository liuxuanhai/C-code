// ±‡≥Ã¡∑œ∞ 6.11 (1)
#include <iostream>
#include <cctype>
int main()
{
	using namespace std;
	char ch;
	
	while (cin.get(ch) && ch != '@')
	{
		if (!isdigit(ch))
		{
			if (islower(ch))
				ch = toupper(ch);
			else if (isupper(ch))
				ch = tolower(ch);
			cout << ch;
		}
	}

	return 0;
}