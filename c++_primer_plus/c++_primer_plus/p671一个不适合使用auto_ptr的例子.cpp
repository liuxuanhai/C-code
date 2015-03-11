// 创建: 2013‎年‎12‎月‎18‎日 0‏‎0:13:59
// 复习: 2014年08月19日 16:14:24 # 1

#include <iostream>
#include <string>
#include <memory>

//#define AUTO_PTR
#define UNIQUE_PTR
//#define SHARED_PTR

#ifdef UNIQUE_PTR
std::unique_ptr<std::string> demo()
{
	std::unique_ptr<std::string> tmp(new std::string("unique_str允许的赋值之一"));
	return tmp;
}
#endif

int main()
{

	using namespace std;
#ifdef AUTO_PTR
	auto_ptr<string> films[5] = 
	{
		auto_ptr<string> (new string("Fowl Balls")),
		auto_ptr<string> (new string("Duck Walks")),
		auto_ptr<string> (new string("Chicken Runs")),
		auto_ptr<string> (new string("Turkey Errors")),
		auto_ptr<string> (new string("Goose Eggs"))
	};
	auto_ptr<string> pwin;
	pwin = films[2];  // films[2] 失去了所有权 这表明film[2]不再引用该字符串

	{ // # 1
		auto_ptr<string> temp = pwin;	// pwin失去所有权 # 1
		cout << *temp << "... 在temp失效后, 所有权不会转换给pwin\n";
	}

#elif defined SHARED_PTR
	shared_ptr<string> films[5] = 
	{
		shared_ptr<string> (new string("Fowl Balls")),
		shared_ptr<string> (new string("Duck Walks")),
		shared_ptr<string> (new string("Chicken Runs")),
		shared_ptr<string> (new string("Turkey Errors")),
		shared_ptr<string> (new string("Goose Eggs"))
	};
	shared_ptr<string> pwin;
	pwin = films[2];  // 这里将引用计数从一增加到二
#elif defined UNIQUE_PTR
	unique_ptr<string> films[5] = 
	{
		unique_ptr<string> (new string("Fowl Balls")),
		unique_ptr<string> (new string("Duck Walks")),
		unique_ptr<string> (new string("Chicken Runs")),
		unique_ptr<string> (new string("Turkey Errors")),
		unique_ptr<string> (new string("Goose Eggs"))
	};
	unique_ptr<string> pwin;
	//pwin = films[2];  // 这里不像auto_ptr在运行阶段出错, 而是直接在编译阶段就报错了error C2248: “std::unique_ptr<_Ty>::operator =”: 无法访问 private 成员(在“std::unique_ptr<_Ty>”类中声明)

	unique_ptr<string> temp = demo();	// # 1 demo()返回一个临时的unique_ptr, 然后temp拥有了string对象的所有权, 因为demo()返回的对象很快被销毁, 没有机会访问他的无效数据, 所以这里没有理由禁止这种赋值, 神奇的是, 编译器确实允许这种赋值!	
	cout << *temp << endl;	// # 1
	unique_ptr<string> temp1 = unique_ptr<string>(new string("我是从临时右值中创建的"));	// "="右边构造函数创建的临时对象在其所有权转让给pu后就会被销毁
		// 总的来说, 如果源unique_ptr是个临时右值, 编译器允许这样做, 如果源unique_ptr存在一段时间, 编译器禁止这样做; # 1
	cout << *temp1 << endl;

	unique_ptr<string> temp2;
	temp2 = move(temp);		// 使用move()可以执行这种不安全的赋值, 但是这种不安全只是在使用 *temp 的时候, 但是如果后边根本就没有这样做, 那这种赋值就是安全的! 通过C++11的移动构造函数和右值引用, unique_ptr能够判断这是否是安全的    # 1
	cout << *temp2 << endl << endl;

#endif

	cout << "The nominees for best avian baseball film are\n";
	for (int i = 0; i < 5; i++)
#ifndef AUTO_PTR
		cout << *films[i] << endl;
#endif
#ifndef UNIQUE_PTR
	cout << "The winner is " << *pwin << "!\n";
#endif
}