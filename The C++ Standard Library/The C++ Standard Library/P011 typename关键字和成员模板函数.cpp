#include <iostream>
using namespace std;

class Q
{
public: 
	typedef int SubType;
};

template <class TT>
class MyClass
{
public:
	typename TT::SubType * ptr;	// 这里 typename 指出 SubType 是 class TT 中的一个型别, 如果没有typename, SubType会被当成一个 static 成员, 于是, T::SubType * ptr成了一个乘积;
		// 这里任何一个用来替换T的型别, 其内部必须提供一个 inner type 内部型别 SubType 的定义
		// C++ 的一般规则是除了typename修饰之外, template内的任何标识符号都被视为一个值而非一个型别

	template <class T/* = int*/>	// error C4519: 仅允许在类模板上使用默认模板参数
	/*virtual*/ void f(T)			// error C2898: “void MyClass::f(T)”: 成员函数模板不能是虚拟的
		// 成员模板函数不能是virtual, 也不能有缺省参数
	
	{
		cout << "MyClass f()" << endl;
	}
};

// 成员模板函数通常用来为template classes 中的成员提供自动型别转换
template <typename T>
class YourClass
{
public:
	YourClass(T t) { Tvalue = t; }
private:
	T Tvalue;
public:
	void assign(YourClass<T> & yourclass)	// 这里使用的参数型别是一个模板参数YourClass<T>, 使得youclass成功被表示为 "型别T的YourClass类的一个对象的引用" (即为成员yourclass提供了型别转换)
		// "必须精确吻合", 即使YourClass<double>和YourClass<int>之间可以进行自动类型转换
	{
		Tvalue = yourclass.Tvalue;
		cout << Tvalue << endl;
	}
	void assign(const int & i)
	{
		cout << i << endl;
	}
	template <class TT>	// 放宽"必须精确吻合"的方法
	void assign2(const YourClass<TT> & yourclass)
	{
		//Tvalue = yourclass.Tvalue;	// error C2248: “YourClass<T>::Tvalue”: 无法访问 private 成员(在“YourClass<T>”类中声明)
		// 由于这里声明的YourClass<TT>可能跟YourClass<T>(比如在YourClass<int>类中访问YourClass<double>类中的私有变量)根本不是同一个类, 所以在这里yourclass就有可能不能访问私有变量了, 所以这里就该使用个getValue()之类的公有函数
		Tvalue = yourclass.getValue();
		cout << Tvalue << endl;
	}
public:
	T getValue() const { return Tvalue; }
};

int main()
{
	//MyClass<int> myclass;		// error C2039: “SubType”: 不是“`global namespace'”的成员
	MyClass<Q> myclass;
	myclass.f<int>(0);

	YourClass<int> intYourClass(1);
	intYourClass.assign(YourClass<int>(2));	// 这里使用的是void assign(YourClass<T> & yourclass); 这里使用这里的参数没有加上const, 但是却能成功生成临时变量让参数引用, 是因为这是类的缘故??? // 是因为2是一个非左值, 经过类型转换变成了一个临时对象
	intYourClass.assign(int(3.00));			// 这里使用的是void assign(const int & i), 如果把const去掉将会出错, 因为用基本类型生成的临时变量必须是在有const引用的前提下??? // 这里3.00是一个非左值, 经过int类型转换后为3, 还是一个非左值, const引用非左值必须是const引用才会生成临时变量然后引用临时变量
	intYourClass.assign(4.22);	// const引用形参有一个属性: 假设实参的类型与引用参数类型不匹配, 但是可以被转换成引用类型, 程序将会创建一个正确类型的临时变量, 使用转换后的实参值来初始化它, 然后 传递一个指向该临时变量的引用.

	// 4. 引用甚至可以初始化为任何左值, 但是非左值只能用const引用来初始化, 因为非左值进行初始化的时候将会产生临时变量, 而我们使用引用作为函数参数的理由是想让他改变程序变量的值而不是临时变量的值, 所以这样可能发生不易发现的错误, 所以干脆禁止了产生临时变量, 除非你告诉c++我的是const引用, 本来就不打算修改值.
//    const引用形参有一个属性: 假设实参的类型与引用参数类型不匹配, 但是可以被转换成引用类型, 程序将会创建一个正确类型的临时变量, 使用转换后的实参值来初始化它, 然后 传递一个指向该临时变量的引用.
//    左值: 变量, 数组元素, 结构成员, 引用和解除引用的指针, 非左值包括字面常量(用引号括起来的字符串除外, 它们由其地址表示)和包含多项的表达式
//    右值: 不能通过地址访问的值

	//intYourClass.assign(YourClass<double>(5.0));	
		// 即使两个型别之间可以实现自动转换, 这里还是要求"必须精确吻合"
		// 放宽"必须精确吻合"的方法: 提供不同template型别(只要型别可被赋值);
	intYourClass.assign2(YourClass<double>(5.0));	
}