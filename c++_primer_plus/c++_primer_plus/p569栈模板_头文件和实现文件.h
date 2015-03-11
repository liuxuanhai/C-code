// 类模板和成员函数模板并不是类和成员函数定义, 他们是c++编译器指令, 说明了如何生成类和成员函数定义, 实例化(具体化)的时候会由编译器生成具体的代码
// 由于模板不是函数, 他们不能单独编译, 模板必须与特定的模板实例话请求一起使用, 为此, 最简单的方法是将所有的模板信息放在一个头文件中, 并在要使用这些模板的文件中包含该头文件
#ifndef 程序清单14_13
#define 程序清单14_13
// 可以把class或typename当做类型的说明符, 就跟int是变量的说明符一样
template <class Type>  // template<Typename Type> 泛型标示符Type这里被称为类型参数, 类似于变量, 但是赋值给他们的是类型而不是数值
// 将具体的类型作为参数传递给这个类
class Stack
{
private:
	enum{MAX = 10};
	Type items[MAX];
	int top;
public:
	Stack();
	bool isempty() {return top == 0;}  // 如果在类声明中定义了方法(内联定义), 则可以省略前缀和类限定符
	bool isfull();
	bool push(const Type & item);  // add
	bool pop(Type & item);  // decerate
};

template <class Type> Stack<Type>::Stack()
{
	top = 0;
}

//template <class Type>
//bool Stack<Type>::isempty()
//{
//	return top == 0;
//}

template <class Type> bool Stack<Type>::isfull()
{
	return top == MAX;
}

template <class Type> bool Stack<Type>::push(const Type & item)
{
	if (top < MAX)
	{
		items[top++] = item;
		return true;
	}
	else
		return false;
}

template <class Type> bool Stack<Type>::pop(Type & item)
{
	if (top > 0)
	{
		item = items[--top];
		return true;
	}
	else
		return false;
}

#endif