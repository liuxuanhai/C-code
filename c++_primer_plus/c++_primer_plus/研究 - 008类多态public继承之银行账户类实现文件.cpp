#include <iostream>
#include "研究 - 008类多态public继承之银行账户类.h"

using std::cout;
using std::endl;
using std::string;

typedef std::ios_base::fmtflags format;
typedef std::streamsize precis;
format setFormat();
void restore(format f, precis p);

// Brass methods
Brass::Brass(const string & s, long an, double bal) : strFullName(s)
{
	lAccNum		= an;
	dbBalance	= bal;
}

void Brass::Deposit(double amt)
{
	if (amt < 0)
		cout << "Error: Negative deposit not allowed; Deposit is cancelled.\n";
	else
		dbBalance += amt;
}

void Brass::Withdraw(double amt)
{
	// set up ###.## format
	format initialState = setFormat();
	precis prec = cout.precision(2);

	if (amt < 0)
		cout << "Withdrawal amount must be positive; Withdrawal canceled.\n";
	else if (amt <= dbBalance)
		dbBalance -= amt;
	else
		cout << "Error: Withdrawal amount of $" << amt
			 << " exceeds your balance.\n"
			 << "Withdrawal canceled.\n";
	restore(initialState, prec);
}

void Brass::ViewAcct() const
{
	// set up ###.## format
	format initialState = setFormat();
	precis prec = cout.precision(2);
	cout << "Client: " << strFullName << endl;
	cout << "Account Number: " << lAccNum << endl;
	cout << "Balance: $" << dbBalance << endl;
	restore(initialState, prec);
}

// BrassPlus Methods
BrassPlus::BrassPlus(const string & s, long an, double bal, double ml, double r) : Brass(s, an, bal)
{
	dbMaxLoan	= ml;
	dbOwesBank	= 0.0;
	dbRate		= r;
}

BrassPlus::BrassPlus(const Brass & ba, double ml, double r) : Brass(ba)
{
	dbMaxLoan	= ml;
	dbOwesBank	= 0.0;
	dbRate		= r;
}

// 重写 redefine hoe ViewAcct() works
void BrassPlus::ViewAcct() const
{
	format initialState = setFormat();
	precis prec = cout.precision(2);
	
	Brass::ViewAcct();  // 显示基类信息
	cout << "Maximum loan: $" << dbMaxLoan << endl;
	cout << "Owed to bank: $" << dbOwesBank << endl;
	cout.precision(3);
	cout << "Loan Rate: " << 100 * dbRate << "%\n";

	restore(initialState, prec);
}

void BrassPlus::Withdraw(double amt)
{
	// set up ###.## format
	format initialState = setFormat();
	precis prec = cout.precision(2);

	double bal = GetBalance();  // 调用了基类的balance方法, 由于没有在派生类中重写该方法, 所以可以不加上作用域解析符
	if (amt <= bal)  // 如果本次取款后还有存款
		Brass::Withdraw(amt);
	else if (amt <= bal + dbMaxLoan - dbOwesBank)  // 如果透支在允许范围内
	{
		double advance = amt - bal;  // 银行贷款额
		dbOwesBank += advance * (1.0 + dbRate);  // 欠银行的钱
		cout << "Bank advance: $" << advance << endl;
		cout << "Finance charge: $" << advance * dbRate << endl;

		//=========== 将余额归零 ==========
		Deposit(advance);  
		Brass::Withdraw(amt); 
		//=================================
	}
	else  // 超出了透支范围
		cout << "Error: Credit limit exceeded. Transaction cancelled.\n";

	restore(initialState, prec);
}

format setFormat()
{
	// set up ###.## format
	return cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
}

void restore(format f, precis p)
{
	cout.setf(f, std::ios_base::floatfield);
	cout.precision(p);
}