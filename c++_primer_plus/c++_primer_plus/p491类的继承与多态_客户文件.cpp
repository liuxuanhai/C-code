// 程序清单 13.10
#include <iostream>
#include "p491类的继承与多态_头文件.h"

int main(void)
{
	using std::cout;
	using std::endl;

	Brass Piggy("Porcelot Pigg", 381299, 4000.00);
	BrassPlus Hoggy("Horatio Hogg", 382288, 3000.00);
	
	Piggy.ViewAcct();
	cout << endl;
	
	Hoggy.ViewAcct();
	cout << endl;
	
	cout << "Depositing $1000 into the Hogg Account: \n";
	Hoggy.Deposit(1000.00);
	cout << "New balance: $" << Hoggy.Balance() << endl << endl;
	
	cout << "Withdrawing $4200 from the Pigg Account:\n";
	Piggy.Withdraw(4200.00);
	cout << "Pigg account balance: $" << Piggy.Balance() << endl << endl;
	
	cout << "Withdrawing $4200 from the Hogg Account: \n";
	Hoggy.Withdraw(4200.00);
	Hoggy.ViewAcct();

	return 0;
}
#else
// 程序清单 13.10 演示多态性
#include <iostream>
#include "p491类的继承与多态_头文件.h"

const int CLIENTS = 4;

int main(void)
{
	using std::cin;
	using std::cout;
	using std::endl;

	Brass * p_clients[CLIENTS];  // 一个基类类型的数组
	std::string temp;
	long tempnum;
	double tempbal;
	char kind;

	for (int i = 0; i < CLIENTS; i++)
	{
		cout << "Enter client's name: ";
		getline(cin, temp);
		cout << "Enter client's account number: ";
		cin >> tempnum;
		cout << "Enter opening balance: $";
		cin >> tempbal;
		cout << "Enter 1 for Brass Account or 2 for BrassPlus Account: ";
		while (cin >> kind && (kind != '1' && kind != '2'))
			cout << "Enter either 1 or 2: ";
		if (kind == '1')
			p_clients[i] = new Brass(temp, tempnum, tempbal);
		else
		{
			double tmax, trate;
			cout << "Enter the overdraft limit: $";
			cin >> tmax;
			cout << "Enter the interest rate as a decimal fraction: ";
			cin >> trate;
			p_clients[i] = new BrassPlus(temp, tempnum, tempbal, tmax, trate);
		}
		while (cin.get() != '\n')
		continue;
	}
	

	for (int i = 0; i < CLIENTS; i++)
	{
		p_clients[i]->ViewAcct();
		cout << endl;
	}

	for (int i = 0; i < CLIENTS; i++)
	{
		delete p_clients[i];  // 如果析构函数不是虚的, 则将只调用对应于指针类型的析构函数 如果析构函数时虚的, 将会调用相对应对象类型的析构函数, 如果指针指向的是BrassPlus对象, 则将调用BrassPlus的析构函数, 然后调用基类的构造函数, 因此 使用虚析构函数能够保证正确的析构函数 序列 被调用
		// 将析构函数定义为虚的将会在执行上述代码的时候使用动态联编, 调用派生类的析构函数, 基类是派生类的一部分, 派生类失效的时候会调用基类的析构函数, 这样两个析构函数就都得到了调用
	}

	cout << "Done!\n";

	return 0;
}