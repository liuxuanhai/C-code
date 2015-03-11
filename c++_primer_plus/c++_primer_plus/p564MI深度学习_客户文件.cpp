#include <iostream>
#include <cstring>
#include "p560MI深度学习_头文件.h"
const int SIZE = 5;

int main()
{
	using std::cin;
	using std::cout;
	using std::endl;
	using std::strchr;

	// ============ 测试通过作用域解析符实现对基类方法的调用 =======
	SingingWaiter S ("HeShixiong", 2005, 6, 1);
	S.Singer::Show();
	cout << endl;
	S.Worker::Show();

	Worker * lolas[SIZE];

	int ct;
	for (ct = 0; ct < SIZE; ct++)
	{
		char choice;
		cout << "Enter the employee category: \n"
			<< "w: waiter  s: singer  "
			<< "t: singing waiter  q: qiut\n";
		cin >> choice;
		while (strchr("wstq", choice) == NULL)
		{
			cout << "Please enter a w, s, t, or q:  ";
			cin >> choice;
		}
		if (choice == 'q')
			break;
		switch (choice)
		{
			case 'w': lolas[ct] = new Waiter; break;
			case 's': lolas[ct] = new Singer; break;
			case 't': lolas[ct] = new SingingWaiter; break;
		}
		cin.get();
		lolas[ct]->Set();
	}

	cout << "\nHere is your staff: \n";
	int i;
	for (i = 0; i < ct; i++)
	{
		cout << endl;
		lolas[i]->Show();
	}
	for (i = 0; i < ct; i++)
		delete lolas[i];
	cout << "Bye.\n";

	return 0;
}