#include <iostream>
#include <string>
#include <cctype>
#include "p569栈模板_头文件和实现文件.h"
using std::cout;
using std::cin;
using std::endl;

int main()
{
	Stack<std::string> st;
	// Stack<char *>st; 是不对的, 因为这仅仅创建了指针, 没有创建用于保存输入字符串的空间, 程序将通过编译, 但是在cin试图将输入保存在木屑不合适的内存单元的时候会崩溃
	char ch;
	std::string po;
	cout << "Please enter A to add a purchase order,\nP to process a PO, or Q to quit.\n";
	while (cin >> ch && std::toupper(ch) != 'Q')
	{
		while (cin.get() != '\n')
			continue;
		if (!std::isalpha(ch))
		{
			cout << '\a';
			continue;
		}
		switch (ch)
		{
		case 'A':
		case 'a': cout << "Enter a PO number to add: ";
				  cin >> po;
			      if (st.isfull())
				      cout << "Stack already full.\n";
				  else
					  st.push(po);
				  break;
		case 'p':
		case 'P': if (st.isempty())
					  cout << "Stack already empty.\n";
				  else
				  {
					  st.pop(po);  // po 此时为弹出的数据临时保存变量
					  cout << "PO #" << po << " popped\n";
					  break;
				  }
		}
		cout << "Please enter A to add a purchase order,\nP to process a PO, or Q to quit.\n";
	}
	cout << "Bye.\n";

	return 0;
}