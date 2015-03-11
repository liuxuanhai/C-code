#ifndef WORKER_H_
#define WORKER_H_
#include <string>

class Worker  // an abstract base class
{
private:
	std::string fullname;
	long id;
protected:
	virtual void Data() const;
	virtual void Get();
public:
	Worker() : fullname("no one"), id(0L) {}
	Worker(const std::string & s, long n) : fullname(s), id(n) {}
	virtual ~Worker() = 0;  // 纯虚函数, 导致这个类不能实例化对象
	virtual void Set();
	virtual void Show() const = 0;
};
     // 去掉virtual error C2385: 对“Worker”的访问不明确  因为Singer表示的是virtual, 但是这里没有表示
class Waiter : virtual public Worker  // 声明Worker为虚基类, 虚基类使得从多个类(他们的基类相同)派生出的对象只继承一个基类对象
{
private:
	int panache;
protected:
	virtual void Data() const;
	virtual void Get();
public:
	Waiter() : Worker(), panache(0) {}        
	Waiter(const std::string & s, long n, int p = 0) : Worker(s, n), panache(p) {}  
	Waiter(const Worker & wk, int p = 0) : Worker(wk), panache(p) {}
	void Set();
	void Show() const;
};

class Singer : virtual public Worker
{
protected:
	enum {other, alto, contralto, soprano, bass, baritone, tenor};
	enum {Vtypes = 7};
	virtual void Data() const;
	virtual void Get();
private:
	static char * pv[Vtypes];
	int voice;
public:
	Singer() : Worker(), voice(other) {}
	Singer(const std::string & s, long n, int v = other) : Worker(s, n), voice(v) {}
	Singer(const Worker & wk, int v = other) : Worker(wk), voice(v) {}
	void Set();
	void Show() const;
};

class SingingWaiter : public Singer, public Waiter
{
protected:
	void Data() const;
	void Get();
public:
	SingingWaiter(){}
	SingingWaiter(const std::string & s, long n, int p = 0, int v = other ) : Worker(s, n), Waiter(s, n, p), Singer(s, n, v) {} 
	SingingWaiter(const Worker & wk, int p = 0, int v = other) : Worker(wk), Waiter(wk, p), Singer(wk, v) {}
	SingingWaiter(const Waiter & wt, int v = other) : Worker(wt), Waiter(wt), Singer(wt, v) {}
	SingingWaiter(const Worker & wt, int p = 0) : Worker(wt), Waiter(wt, p), Singer() {}  // 把Singer(wk)写成了Singer()完全没问题
	// c++在基类是虚的时, 禁止信息通过中间类自动传递给基类, 所以Waiter(wk, p)中的wk只是起到了明确使用Waiter哪个构造函数的作用, 但是wk是不能传进去的
	// 这里调用了基类的基类的构造函数, 在非虚基类是非法的, 在这里是合法的, 如果不写Worker(wk)将会调用默认的
	void Set();
	void Show() const;
};

#endif