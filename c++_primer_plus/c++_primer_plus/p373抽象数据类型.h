// 程序清单 10.10 头文件 -- 自己制作的栈
#ifndef STAKC_H_
#define STAKC_H_

typedef unsigned long Item;  // 如果需要double栈或者结构类型的栈, 则只需修改typedef语句, 而类声明和方法定义保持不变 14章的类模板提供了功能更强大的方法, 来将储存的数据类型与类设计隔离开来

class Stack  // 在类中定义的名称(如类数据成员和类成员函数名)的作用域为整个类, 他们在类外是未知的. 这便使得不能从外部直接访问类的成员, 公有成员函数也是如此. 也就是说, 要调用公有成员函数, 必须通过对象, 而在定义成员函数的时候也必须使用作用域解析符
{
private:
	//const int max = 12;  // error C2864: “Stack::max”: 只有静态常量整型数据成员才可以在类中初始化    错误原因: 声明类只是描述了对象的形式, 并没有创建对象, 因此在创建对象前, 将没有用于储存值的空间
	//static const int max = 10;		// 这将会创建一个名为max的常量, 该常量将会与其他静态变量储存在一起, 而不是存在对象中
	enum {MAX = 10};  // constant specific to class  // 用这种方式声明枚举并不会创建类数据成员, 也就是说所有对象中都不包含枚举, MAX只是一个符号名称, 在作用域为整个类的代码中遇到他时, 编译器用30代替他
		// 枚举: 他创建了一种新的"类型", 并且描述了他可以具有的值, 但是他没有创建新的变量(如enum aaa = MAX), 所以他不需要存储值的空间
	Item items[MAX];   // holds stack items		// 私有部分说明栈是使用数组实现的, 但是公有部分隐藏了这一点, 因此可以使用动态数组来代替数组, 而不会改变类的接口, 这意味着修改栈的实现后, 不需要重新编写使用栈的程序
	int top;		     // index for top stack item
public:
	Stack();
	bool isempty() const;
	bool isfull() const;
	// push() returns false if stack already is full, true otherwise
	bool push(const Item & item);  // add item to stack
	// pup() returns false if stack already is empty, true otherwise
	bool pop(Item & item);  // pop top into item
};
#endif