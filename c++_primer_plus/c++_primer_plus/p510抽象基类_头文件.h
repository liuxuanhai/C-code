// 抽象基类 (abstract base class)ABC 抽象基类编程称为ABC编程: 只定义接口, 不涉及实现
// 抽象基类至少包含一个纯虚函数(= 0)
// 别把抽象基类和虚基类搞混了(虚基类在继承的时候使用的是class A : virtual class B {};)
#ifndef 抽象基类13_11
#define 抽象基类13_11
#include <iostream>
#include <string>

class AcctABC  // 包含纯虚函数使他成为了抽象基类
{
private:
	std::string fullName;
	long acctNum;
	double balance;
protected:
	struct Formatting
	{
		std::ios_base::fmtflags flag;
		std::streamsize pr;
	};
	const std::string & FullName() const {return fullName;}
	long AcctNum() const {return acctNum;}  // 专门提供给派生类用来改变基类private成员的保护函数, 这比直接将基类的属性设置为protected要好, 因为这样基类的私有成员只有几个接口能被外部访问
	Formatting SetFormat() const;
	void Restore(Formatting & f) const;
public:
	AcctABC(const std::string & s = "Nullbody", long an = -1, double bal = 0.0);
	void Deposit(double amt);
	virtual void Withdraw(double amt) = 0;
	double Balance () const {return balance;}
	virtual void ViewAcct() const = 0;
	virtual ~AcctABC(){}  // 保证析构函数正确的执行顺序
};

class Brass : public AcctABC
{
public:
	Brass(const std::string & s = "Nullbody", long an = -1, double bal = 0.0) : AcctABC(s, an, bal){}
	virtual void Withdraw(double amt);
	virtual void ViewAcct() const;
	virtual ~Brass(){}
};

class BrassPlus : public AcctABC
{
private:
	double maxLoan;
	double rate;
	double owesBank;
public:
	BrassPlus(const std::string & s = "Nullbody", long an = -1, double bal = 0.0, double ml = 500, double r = 0.10);
	BrassPlus(const Brass & ba, double ml = 500, double r = 0.1);
	virtual void ViewAcct() const;
	virtual void Withdraw(double amt);
	void RestMax(double m){maxLoan = m;}
	void RestRate(double r){rate = r;}
	void RestOwes(){owesBank = 0;}
};
#endif