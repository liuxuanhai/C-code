//  程序清单 10.12 客户文件 -- 模拟售货员的行为, 使用栈的先进后出方式, 从购物车的最上面开始处理购物订单
#include <iostream>
#include <cctype>
#include "p373抽象数据类型.h"
int main()
{
	using namespace std;
	Stack st;  // create an empty stack
	char ch;
	unsigned long po;
	cout << "Please enter A to add a purchase order.\n"
		<< "P to process a PO, or Q to quit.\n";
	while (cin >> ch && toupper(ch) != 'Q')
	{
		while (cin.get() != '\n')
			continue;
		if (!isalpha(ch))
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
					 cout << "stack already full\n";
				 else
					 st.push(po);
				 break;
		case 'P':
		case 'p': if (st.isempty())
					  cout << "stack already empty\n";
				  else{
					  st.pop(po);
					  cout << "PO #" << po << " popped\n";
				  }
				  break;
		}
		cout << "Please enter A to add a purchase order,\n"
			<< "P to process a PO, or Q to quit.\n";
	}
	cout << "Bye\n";
	return 0;
}