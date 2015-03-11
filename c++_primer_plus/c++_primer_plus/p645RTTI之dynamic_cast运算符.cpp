// 创建 2013 12 16 17
// 复习 2014 08 18 18 # 1

// RTTI(Runtime Type Identification)运行阶段类型识别
#include <iostream>
#include <cstdlib>
#include <ctime>
//#include <typeinfo>	// 定义dynamic_cast中的bad_cast异常(exception中继承)

using std::cout;
class Grand
{
private:
	int hold;
public:
	Grand(int h = 0) : hold(h) {}
	//virtual ~Grand() {} 书中没有加上这个, 这回导致问题吗?????????
	virtual void Speak() const {cout << "I am a grand class;";}	// Grand Superb Magnificent 都有定义 # 1
	virtual int Value() const {return hold;}
};

class Superb : public Grand
{
public:
	Superb(int h = 0) : Grand(h) {} 
	void Speak() const {cout << "I am a superb class!!";}
	virtual void Say() const {cout << "I hold the superb value of " << Value() << "!\n";}	// Superb Magnificent 有定义 # 1
};

class Magnificent : public Superb
{
private:
	char ch;
public:
	Magnificent(int h = 0, char c = 'A') : Superb(h), ch(c) {}
	void Speak() const {cout << "I am a magnificent class.";}
	void Say() const {cout << "I hold the character " << ch << " and the integer " << Value() << "!\n";}
};

Grand * GetOne();

int main()
{
	std::srand(static_cast<unsigned long>(std::time(0)));
	Grand * pg;
	Superb * ps;

		// 关于指针的用法

	cout << "关于指针返回nullptr: \n\n";
	for (int i = 0; i < 5; i++)
	{
		pg = GetOne();
		pg->Speak();
		if (ps = dynamic_cast<Superb *>(pg))  // 如果是安全的返回类指针, 否则空指针
			// 这里实现了动态类型识别: Superb, Magnificent都能识别出来 # 1
			// 这里使用的是返回nullptr来标识不能实现安全的转换, 但是当类型是引用的时候, 没有与空指针对应的引用值, 无法用特殊值来标识失败, 这时候dynamic_cast将会一引发bad_cast异常(exception中继承而来)
			ps->Say();
	}

		// 关于引用引发bad_cast异常 # 1

	cout << "\n\n关于引用引发bad_cast异常:\n\n";
	for (int i = 0; i < 5; i++)
	{
		pg = GetOne();
		Grand & temp = *pg;
		try
		{
			temp.Speak();
			Superb & temp1 = dynamic_cast<Superb &>(temp);	// 如果失败的话, 引发bad_cast异常, 下边的语句不执行, 直接跳到try块的结束花括号 # 1
			temp1.Say();
		}
		catch(std::bad_cast)
		{
			cout << "这个是Grand类.\n";
		}
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