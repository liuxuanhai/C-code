// 编程练习 10.10 (5) 客户文件
#include <iostream>
#include "p378编程练习5.h"

int main()
{
	using namespace std;
	Stack st;
	Item cus[10];

	for (int i = 0; i < 10; i++)
	{
		cout << "输入姓名(空行退出): ";
		if (cin.getline(cus[i].fullname, 35) 
			&& cus[i].fullname[0] != '\0')
		{
			cout << "输入价格: ";
			cin >> cus[i].payment;
			while (cin.get() != '\n');
			if (!st.add(cus[i]))
				break;
		}
		else
			break;
	}
	st.show();
	st.de();
	st.show();
	st.de();
	st.show();

	return 0;
}