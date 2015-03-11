// 程序清单 10.6 客户文件
#include <iostream>
#include "p356构造函数和析构函数.h"
// 不能像初始化结构一样初始化类对象, 因为类的数据部分的访问状态是私有的, 这意味着不能直接访问数据成员, 但是能够通过成员函数来访问数据成员, 因此需要设计合适的成员函数------构造函数

int main()
{
	{
		using std::cout;
		cout << "####Using constructors to create new objects####\n";
		Stock stock1("NanoSmart", 12, 20.0);  // syntax 1  // 无法使用对象来调用构造函数, 因为在构造函数构造出对象之前, 对象是不存在的, 因此构造函数被用来创建对象, 而不能通过对象来调用, 所以下面用到构造函数的时候都没用使用作用域解析符::
		stock1.show();
		Stock stock2 = Stock ("Boffo Objects", 2, 2.0);  // syntax 2
			// c++允许编译器用两种方法来实现这样的初始化方式: 1. 与syntax 1语法完全相同 本编译器就是这样做的 2. 允许调用构造函数来创建以个临时对象, 然后将该临时对象复制到stock2中, 并丢弃它. 如果编译器使用的是这种方式, 则将会为临时变量调用析构函数
		stock2.show();

		cout << "@@@Assigning stock1 to stock2:@@@\n";
		stock2 = stock1;
		cout << "@@@Listing stock1 and stock2:@@@\n";
		stock1.show();
		stock2.show();

		cout << "#@@#Using a constructor to reset an object#@@#\n";
		stock1 = Stock("Nifty Foods", 10, 50.0);  // temp object
			// 构造函数不仅仅可用于初始化新对象, 这里stock1对象已经存在, 因此这条语句不是对stock1进行的初始化, 而是将新值赋给他, 这是通过让构造程序创建一个新的, 临时的对象, 然后将其内容复制给stock1来实现的. 随后程序调用析构函数, 以删除该临时对象, 有些编译器可能要过一段时间才删除临时对象,, 因此析构函数的调用将会延迟
		cout << "$$Revised stock1:$$\n";
		stock1.show();
		cout << "Done\n";
	}  // 在这里局部变量(stock1和stock2)将消失, 由于这种自动变量被放在栈中, 因此最后创建的对象将会最先被删除, 最先创建的对象最后被删除(NanoSmart最初位于stock1中, 但是随后被传输到stock2中, 然后stock1被重置为Nifty Food);

	return 0;
}