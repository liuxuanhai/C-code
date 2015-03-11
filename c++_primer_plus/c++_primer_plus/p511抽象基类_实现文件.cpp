#include <iostream>
#include "p510抽象基类_头文件.h"

using std::cout;
using std::ios_base;
using std::endl;
using std::string;

AcctABC::AcctABC(const string & s, long an, double bal)
{
	fullName = s;
	acctNum = an;
	balance = bal;
}

void AcctABC::Deposit(double amt)
{
	if (amt < 0)
		cout << "!Error: Negative deposit not allowed; Deposit is cancelled.\n";
	else
		balance += amt;
}

// 声明: virtual void Withdraw(double amt) = 0;
// 声明为纯虚函数的函数也可以在本类中进行定义, (ERROR:)xxxxxx这样如果派生类中没有重写这个函数的话将会使用基类中的方法xxxxx 正确的原因是在派生类中重新定义的时候可以引用基类的抽象方法, 这样就可以访问基类的数据了
											// 错误, 派生类中必须重写纯虚函数, 如果没有重写的话他将会是一个抽象的派生类不能实例化对象
void AcctABC::Withdraw(double amt)   // 对虚函数的定义, 等待派生类中重写, 如果没有重写的化将会使用这个
{
	balance -= amt;
}

AcctABC::Formatting AcctABC::SetFormat() const
{
	Formatting f;
	f.flag = cout.setf(ios_base::fixed, ios_base::floatfield);
	f.pr = cout.precision(2);
	return f;
}

void AcctABC::Restore(Formatting & f) const
{
	cout.setf(f.flag, ios_base::floatfield);
	cout.precision(f.pr);
}

void Brass::Withdraw(double amt)
{
	if (amt < 0)
		cout << "!Error: Withdrawal amount must be positive; Withdrawal canceled.\n";
	else if (amt <= Balance())
		AcctABC::Withdraw(amt);  // 使用了基类抽象方法
	else
		cout << "!Error: Withdrawal amount of $" << amt
			 << " exceeds your balance.\n"
			 << "Withdrawal canceled.\n";
}

void Brass::ViewAcct() const
{
	Formatting f = SetFormat();
	cout << "Brass Client: " << FullName() << endl;
	cout << "Account Number: "<< AcctNum() << endl;
	cout << "Balace: $" << Balance() << endl;
	Restore(f);
}

BrassPlus::BrassPlus(const string & s, long an, double bal, double ml, double r) : AcctABC(s, an, bal)
{
	maxLoan = ml;
	owesBank = 0.0;
	rate = r;
}

BrassPlus::BrassPlus(const Brass & ba, double ml, double r) : AcctABC(ba)  // 在AcctABC中我并没有定义接受AcctABC的构造函数(复制函数), 系统会自动生成一个(如果没有动态分配内存的话这不会引起错误)
{
	maxLoan = ml;
	owesBank = 0.0;
	rate = r;
}

void BrassPlus::ViewAcct() const
{
	Formatting f = SetFormat();

	cout << "BrassPlus Client: " << FullName() << endl;
	cout << "Account Number: "<< AcctNum() << endl;
	cout << "Balace: $" << Balance() << endl;
	cout << "Maximum loan: $" << maxLoan << endl;
	cout << "Owed to bank: $" << owesBank << endl;
	cout.precision(3);
	cout << "Loan Rate: " << 100 * rate << "%\n";

	Restore(f);
}

void BrassPlus::Withdraw(double amt)
{
	Formatting f = SetFormat();

	double bal = Balance();
	if (amt <= bal)
		AcctABC::Withdraw(amt);
	else if (amt <= bal + maxLoan - owesBank)  // 如果透支在允许范围内
	{
		double advance = amt - bal;  // 银行贷款额
		owesBank += advance * (1.0 + rate);  // 欠银行的钱
		cout << "Bank advance: $" << advance << endl;
		cout << "Finance charge: $" << advance * rate << endl;

		//=========== 将余额归零 ==========
		Deposit(advance);  
		AcctABC::Withdraw(amt); 
		//=================================
	}
	else  // 超出了透支范围
		cout << "Error: Credit limit exceeded. Transaction cancelled.\n";

	Restore(f);
}