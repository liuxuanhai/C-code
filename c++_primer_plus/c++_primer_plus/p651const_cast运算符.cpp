// 创建: 2013 12 16 18
// 复习: 2014 08 15 14 # 1

// 四个类型转换运算符: # 1
//		dynamic_cast, 使得能够在累层次结构中进行向上类型转换(由于is-a关系, 这样的类型转换是安全的), 而不允许其他转换    如 base * pfather =  dynamic_cast<base *>(指向派生类对象的指针), 如果不能实现转换, 则将nullptr赋给pfather    如果可能的话, 此运算符使用一个指向基类的指针来生成一个指向派生类的指针, 否则, 运算符返回空指针 !!!注意, dynamic_cast只使用与包含虚函数的多态类类型
//		const_cast, 只能删除const, 类型不能改变 注意: 当改变的是指针类型的时候, 只有指向的值是非const才能实现改变
//		static_cast, static_cast<type-name>(expression) 只有当expression所属的类型可被隐式转换为type-name !或者! type-name可以被隐式转换为expression所属类型的时候, 转换才合法
//		reinterpret_cast

#include <iostream>
using std::cout;
using std::endl;
void change(const int * pt, int n);

class A
{
public:
	int a;
	A(int _a): a(_a){}
	virtual ~A() {};	// dynamic_cast<typename>(expression)要求expression必须为多态类类型, 如果B没有从A中继承一个虚函数, 那么他就不是多态类类型, 至于为什么限制为必须是多态类类型呢 ??? 
};

class B : public A
{
public:
	int b;
	B(int _b, int _a = 12) : A(_a), b(_b){}
};

class C
{
public:
	int c;
};

int main()
{
	int pop1 = 38383;
	const int pop2 = 2000;

	cout << "pop1, pop2: " << pop1 << ", " << pop2 << endl;
	change(&pop1, -103);
	change(&pop2, -103);
	cout << "pop1, pop2: " << pop1 << ", " << pop2 << endl;

	cout << endl << endl;

	int a = static_cast<int>(3.25);		// # 1 可以用static_cast用来替换平时使用的类型转换 # 1
	//int b = static_cast<int>(&a);
	cout << a << endl;

	cout << endl << endl;

	A aa(1);
	cout << aa.a << endl;
	B bb(2);
	cout << bb.b << endl;
	A aaa = bb;	// 将派生类直接赋值给基类(利用了A自动生成的复制构造函数)
	cout << aaa.a << endl;	// aaa的a值更新为12
	//cout << aaa.b << endl;	// 由于aaa的类型为A, 所以没有aaa.b存在
	A * pa = &bb;	// 将bb的地址赋值给pa, 这不同于上边的aaa, 因为上边的aaa事实上已经是A类型了, 但是这里的pa虽然声明的是(A *)类型, 但是赋给他的是(B *)的指针, 所以即使他不能使用pa->b但是可以通过dynamic_cast实现还原为B *
	cout << pa->a << endl;
	//cout << pa->b << endl;	// b被隐藏了
	B * pb = dynamic_cast<B *>(pa);	// 但是这里完全可以使用B * pb = (B *)(pa)啊, 而且B * pb = (C *)(pa)编译器也会报错	// 这里的转换是安全的, 因为pa虽然是(A *)类型, 但是他指向的是(B *)类型的对象, 所以使用B * pb = (B *)(pa)也行, 虽然他不能在不安全的时候返回nullptr
	cout << pb->b << endl;		// b出现了

	B * bbbbb = (B *)&aa;	// 用派生类的指针指向基类
	cout << "....." << bbbbb->a << bbbbb->b << endl;	// 这里bbbbb->b出现了-858993460 这是不安全的
	B * bbbbbb = dynamic_cast<B *>(&aa);				// 这里由于是不安全的, 所以返回的是nullptr, 这就比上边的安全多了 
	if (bbbbbb)
		cout << "....." << bbbbbb->a << bbbbbb->b << endl;

	return 0;
}

void change(const int * pt, int n)
{
	int * pc;
	pc = const_cast<int *>(pt);  // 仅当指向的数据不是const类型才行
	*pc += n;
}