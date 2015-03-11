// 创建 2013 12 16 17
// 复习 2014 08 18 18 # 1

// typeid运算符使得能够确定两个对象是否为同种类型, 它返回一个对type_info对象(头文件typeinfo)的引用 # 1
// typeid(Magnificent) == typeid(*pg);  type_info 对象重载了 == !=, 如果pg是一个空指针, 则引发bad_typeid异常 # 1
// typeid(*pg).name() 返回pg所指向的对象所属的类定义的字符串 # 1
// typeid适用于dynamic_cast和virtual函数不能处理的情况
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <typeinfo>
using namespace std;

class Grand
{
private:
	int hold;
public:
	Grand (int h = 0) : hold(h) {}
	virtual ~Grand() {}
	virtual void Speak() const {cout << "Speak of Grand.\n";}
	virtual int Value() const {return hold;}
};

class Superb : public Grand
{
public:
	Superb(int h = 0) : Grand(h) {}
	virtual void Speak() const {cout << "Speak of Superb.\n";}
	virtual void Say() const {cout << "I hold the superb value of " << Value() << ".\n";}
};

class Magnificent : public Superb
{
private: 
	char ch;
public:
	Magnificent(int h = 0, char cv = 'A') : Superb(h), ch(cv) {}
	void Speak() const {cout << "Speak of Magnificent.\n";}
	void Say() const {cout << "I hold the character " << ch << " and the integer " << Value() << endl;}
};

Grand * GetOne();
int main()
{
	srand(time(0));
	Grand * pg;
	Superb * ps;

	for (int i = 0; i < 5; i++)
	{
		pg = GetOne();
		cout << "Now processing type " << typeid(*pg).name() << "...\n";
		pg->Speak();
		if (ps = dynamic_cast<Superb *> (pg))
			ps->Say();
		if (typeid(Magnificent) == typeid(*pg))	// 这个比 # 1 1 的优势在于 typeid是任何两个类之间比较, 而# 1 1只适用于判断是不是派生类... (详见 # 1 2) # 1
		//if (dynamic_cast<Magnificent *>(pg))	// # 1 1
			cout << "Yes, you are really magnificent.\n";
		if (dynamic_cast<Grand *>(pg))			// # 1 2
			cout << "dynamic_cast vs typeid 的弱点\n";
		cout << endl;
	}

	return 0;
}

Grand * GetOne()
{
	Grand * p;
	switch (std::rand() % 3)
	{
	case 0: p = new Grand(std::rand() % 100); break;
	case 1: p = new Superb(std::rand() % 100); break;
	case 2: p = new Magnificent(std::rand() % 100, 'A' + std::rand() % 26); break;
	}
	return p;
}