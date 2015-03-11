#include <iostream>
#include "p491类的继承与多态_头文件.h"

using std::cout;
using std::endl;
using std::string;

typedef std::ios_base::fmtflags format;
typedef std::streamsize precis;
format setFormat();
void restore(format f, precis p);

// Brass methods
Brass::Brass(const string & s, long an, double bal)
{
	fullName = s;
	acctNum = an;
	balance = bal;
}

void Brass::Deposit(double amt)
{
	if (amt < 0)
		cout << "Error: Negative deposit not allowed; Deposit is cancelled.\n";
	else
		balance += amt;
}

void Brass::Withdraw(double amt)
{
	// set up ###.## format
	format initialState = setFormat();
	precis prec = cout.precision(2);

	if (amt < 0)
		cout << "Withdrawal amount must be positive; Withdrawal canceled.\n";
	else if (amt <= balance)
		balance -= amt;
	else
		cout << "Error: Withdrawal amount of $" << amt
			 << " exceeds your balance.\n"
			 << "Withdrawal canceled.\n";
	restore(initialState, prec);
}

double Brass::Balance() const
{
	return balance;
}

void Brass::ViewAcct() const
{
	// set up ###.## format
	format initialState = setFormat();
	precis prec = cout.precision(2);
	cout << "Client: " << fullName << endl;
	cout << "Account Number: " << acctNum << endl;
	cout << "Balance: $" << balance << endl;
	restore(initialState, prec);
}

// BrassPlus Methods
BrassPlus::BrassPlus(const string & s, long an, double bal, double ml, double r) : Brass(s, an, bal)
{
	maxLoan = ml;
	owesBank = 0.0;
	rate = r;
}

BrassPlus::BrassPlus(const Brass & ba, double ml, double r) : Brass(ba)
{
	maxLoan = ml;
	owesBank = 0.0;
	rate = r;
}

// 重写 redefine hoe ViewAcct() works
void BrassPlus::ViewAcct() const
{
	format initialState = setFormat();
	precis prec = cout.precision(2);
	
	Brass::ViewAcct();  // 显示基类信息
	cout << "Maximum loan: $" << maxLoan << endl;
	cout << "Owed to bank: $" << owesBank << endl;
	cout.precision(3);
	cout << "Loan Rate: " << 100 * rate << "%\n";

	restore(initialState, prec);
}

void BrassPlus::Withdraw(double amt)
{
	// set up ###.## format
	format initialState = setFormat();
	precis prec = cout.precision(2);

	double bal = Balance();  // 调用了基类的balance方法, 由于没有在派生类中重写该方法, 所以可以不加上作用域解析符
	if (amt <= bal)  // 如果本次取款后还有存款
		Brass::Withdraw(amt);
	else if (amt <= bal + maxLoan - owesBank)  // 如果透支在允许范围内
	{
		double advance = amt - bal;  // 银行贷款额
		owesBank += advance * (1.0 + rate);  // 欠银行的钱
		cout << "Bank advance: $" << advance << endl;
		cout << "Finance charge: $" << advance * rate << endl;

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