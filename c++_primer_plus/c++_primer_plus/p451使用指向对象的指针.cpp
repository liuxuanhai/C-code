// 程序清单 12.7
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "p442string类的部分功能的实现.h"
const int ArSize = 10;
const int MaxLen = 81;
int main()
{
	using namespace std;
	cout << "Ten string:\n";
	String sayings[ArSize];
	char temp[MaxLen];
	int i;
	for (i = 0; i < ArSize; i++)
	{
		cout << i << " : ";
		cin.get(temp, MaxLen);
		while (cin && cin.get() != '\n')
			continue;
		if (!cin || temp[0] == '\0')
			break;
		else
			sayings[i] = temp;
	}
	int tot = i;

	if (tot > 0)
	{
		cout << "Here is your sayings:\n";
		for (i = 0; i < tot; i++)
			cout << sayings[i] << '\n';

		String * shortest = &sayings[0];
		String * first = &sayings[0];
		for (i = 1; i < tot; i++)
		{
			if (shortest->length() > sayings[i].length())
				shortest = &sayings[i];
			if (*first > sayings[i])
				first = &sayings[i];
		}
		cout << "Shortest saying:\n" << *shortest << endl;
		cout << "First alphabetically:\n" << *first << endl;
		srand(time(0));
		int choice = rand() % tot;
		String * favorite = new String(sayings[choice]);
		cout << "My favorite saying:\n" << *favorite << endl;
		delete favorite;
	}
	else
		cout << "Not much to say, eh?\n";
	cout << "Bye.\n";

	return 0;
}