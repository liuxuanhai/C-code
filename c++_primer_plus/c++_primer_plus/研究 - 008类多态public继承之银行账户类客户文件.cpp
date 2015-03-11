#include <iostream>
#include "研究 - 008类多态public继承之银行账户类.h"
int main(void)
{
	using std::cout;
	using std::endl;

		// 关于直接使用对象

	Brass Brass1("Brass1", 381299, 4000.00);
	BrassPlus BrassPlus1("BrassPlus1", 382288, 3000.00);

	Brass1.ViewAcct();
	cout << endl;

	BrassPlus1.ViewAcct();
	cout << endl;

	cout << "给账户BrassPlus1存入 $1000: \n";
	BrassPlus1.Deposit(1000.00);
	cout << "最新余额: $" << Brass1.GetBalance() << endl << endl;

	cout << "从Brass1中取出 $4200:\n";
	Brass1.Withdraw(4200);
	cout << "最新余额: $" << Brass1.GetBalance() << endl << endl;

	cout << "从BrassPlus1中取出 $4200:\n";
	BrassPlus1.Withdraw(4200);
	BrassPlus1.ViewAcct();
	cout << endl << endl;

		// 关于多态

	using std::cin;
	const int CLIENTS = 2;

	Brass * pBrass[CLIENTS];
	std::string temp;
	long		tempnum;
	double		tempbal;
	char		kind;

	for (int i = 0; i < CLIENTS; i++)
	{
		cout << "输入客户姓名: ";
		getline(cin, temp);
		cout << "输入客户的账号: ";
		cin >> tempnum;
		cout << "输入金额: $";
		cin >> tempbal;
		cout << "1. 青铜账户	2. 白铜账户\n请选择: ";
		while (cin >> kind && (kind != '1' && kind != '2'))
			cout << "请输入 1 或 2: ";
		if (kind == '1')
			pBrass[i] = new Brass(temp, tempnum, tempbal);
		else
		{
			double tmax, trate;
			cout << "输入透支限额: $";
			cin >> tmax;
			cout << "输入利率: ";
			cin >> trate;
			pBrass[i] = new BrassPlus(temp, tempnum, tempbal, tmax, trate);
		}
		while (cin.get() != '\n');
	}
	cout << endl;
	for (int i = 0; i < CLIENTS; i++)
	{
		pBrass[i]->ViewAcct();
		cout << endl;
	}

	for (int i = 0; i < CLIENTS; i++)
	{
		delete pBrass[i];
	}
	
	cout << "Done!\n";

	return 0;
}