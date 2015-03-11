				// 多态公有继承
//	多态:	方法根据上下文确定自己的实现方式 比如, 基类引用在引用基类对象时候调用基类的show(), 但是在引用派生类对象的时候, 调用的是派生类的show();
//			要想实现多态, 有两种方法:	1. 在派生类中重新定义基类方法.	2. 使用虚函数.
//	虚函数:	如果在派生类重新定义基类的方法, 通常应该将基类方法声明为虚函数, 这样程序会根据对象类型而不是引用类型或指针类型来选择方法版本;
//			为基类声明一个虚析构函数是国际惯例, 派生类不继承基类的构造函数, 所以构造函数为虚函数没意义;
//			如果基类有三个重载函数, 派生类之重写了一个, 那么其他两个会被隐藏, 派生类将会无法使用他们;
//			在基类声明为虚函数的函数在派生类会自动成为虚函数;

#ifndef BRASS_H_
#define BRASS_H_
#include <string>

class Brass	// 黄铜账户
{
private:
	std::string	strFullName;
	long		lAccNum;
	double		dbBalance;	// 余额
public:
	Brass(const std::string & str = "NoBrass", long an = -1, double bal = 0.0);
	void Deposit(double amt);			// 存款函数
	virtual void Withdraw(double amt);	// 取款函数
	double GetBalance() const { return dbBalance; }
	virtual void ViewAcct() const;		// 查看函数
	virtual ~Brass(){}	// 在基类中声明为虚函数的在派生类会自动声明为虚函数, 但是最好加上virtual
	// 基类声明了一个虚析构函数, 这是为了保证释放派生类对象的时候正确的调用析构函数
	// 如果析构函数不是虚的, 则将只调用对应于指针类型的析构函数, 对于本程序, 这意味着只有Brass的析构函数被调用, 即使指针指向的是一个BrassPlus对象;
};

class BrassPlus : public Brass
{
private:
	double dbMaxLoan;	// 最大透支额度
	double dbRate;		// 利率
	double dbOwesBank;	// 欠款金额
public:
	BrassPlus(const std::string & str = "NoBrassPlus", long an = -1,
		double bal = 0.0, double ml = 500, double r = 0.11125);
	BrassPlus(const Brass & ba, double ml = 500, double r = 0.11125);
	virtual void ViewAcct() const;		// 重写基类虚函数
	virtual void Withdraw(double amt);	// 重写基类虚函数
	void ResetMax(double m) { dbMaxLoan = m; }
	void ResetRate(double r) { dbRate = r; }
	void ResetOwes() { dbOwesBank = 0; };
};

#endif