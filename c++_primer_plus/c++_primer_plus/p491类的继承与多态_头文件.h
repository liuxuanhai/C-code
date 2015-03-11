// 一个关于银行账户的类 基类是不能透支用户 派生类是可以透支的用户
// 多态: 基类的成员函数被派生类重写产生了不同的作用  可以用一个基类类型的数组同时包含能够表示派生类的指针, 这就是多态性
// 注意: 如果要在派生类重新定义基类的方法, 通常应该将基类方法声明为虚的, 这样程序将会根据对象类型而不是引用或指针的类型来选择方法版本, 为基类声明一个虚析构函数也是一种惯例
// 仅仅将那些预期会被重写的函数定义为虚函数 // 派生类不继承基类的构造函数, 所以将构造函数生成虚函数也没什么意义
// 通常应该为基类提供一个虚析构函数, 即使他不不需要析构函数, 也不做基类, 这仅仅是牺牲了一点点空间和效率而已
// 如果基类中有3个重载虚函数, 而派生类中只重写了一个, 那么其他两个将会被隐藏, 派生类将会无法使用它们
#ifndef BEASS_H_
#define BEASS_H_
#include <string>
// Brass Account Class
class Brass
{
private:
	std::string fullName;
	long acctNum;
	double balance;  // 余额
public:
	Brass(const std::string & a = "Nullbody", long an = -1, double bal = 0.0);
	void Deposit(double amt);  // 存款函数
	virtual void Withdraw(double amt);  // 取款函数
	double Balance() const;
	virtual void ViewAcct() const;  // 查看账户函数  // 被称为虚方法(virtual method)
	virtual ~Brass() {};  // 在基类中声明为虚方法后在派生类中就会自动成为虚方法, 但是在派生类中声明一下才是更好地办法, 虚方法就跟Animal类的虚参数传进Bird类的对象的时候可以调用Bird的重写函数一样
	// 基类声明了一个虚析构函数, 这是为了保证释放派生类对象的时候正确的调用析构函数
};

class BrassPlus : public Brass
{
private:
	double maxLoan;  // 最大透支额度
	double rate;  // 利息率
	double owesBank;  // 欠款金额
public:
	BrassPlus(const std::string & s = "Nullbody", long an = -1, double bal = 0.0, double ml = 500, double r = 0.11125);
	BrassPlus(const Brass & ba, double ml = 500, double r = 0.11125);
	virtual void ViewAcct()const;  // 重写基类的成员函数
	virtual void Withdraw(double amt);  // 重写基类的成员函数
	void ResetMax(double m){maxLoan = m;}  // 头文件中的内联函数定义
	void ResetRate(double r){rate = r;}
	void ResetOwes(){owesBank = 0;}
};

#endif