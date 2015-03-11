#include <iostream>
#include <cctype>
#include "研究 - 002类之ADT栈.h"

int main(void)
{
	using namespace std;

	Stack	st;
	char	ch;
	unsigned long po;

	cout << "a> Push	b> Pop		c> Quit\n";
	while (cin >>ch && toupper(ch) != 'Q')
	{
		while (cin.get() != '\n');
		if (!isalpha(ch))
		{
			cout << '\a';
			continue;
		}
		switch (ch)
		{
		case 'a':
		case 'A':
			cout << "输入一个int数:\n";
			cin >> po;
			if (st.isFull())
				cout << "栈已经满了, 压入失败!\n";
			else
				st.push(po);
			break;

		case 'p':
		case 'P':
			if (st.isEmpty())
				cout << "栈中是空的, 弹出失败!\n";
			else
			{
				st.pop(po);
				cout << "PO #" << po << " 被弹出!\n";
			}
			break;
		}
		cout << "a> Push	b> Pop		c> Quit\n";
	}

	cout << "Bye\n";

	return 0;
}