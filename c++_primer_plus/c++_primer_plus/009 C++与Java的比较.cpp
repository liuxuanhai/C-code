// 创建: 2014-09-13 13:16:21
// # 1 关于字符 + 数字		C++中不允许, java中默认将"string"转换为String类, 然后String + int是String, int + String还是String
// # 2 构造函数调用构造函数 C++中不允许	 java中支持, 但是只能调用一次this(args)
// # 3 关于(new 对象)临时变量的方法调用的可行性	
	// Java中可以使用 new Obj.mem...
	// C++中使用 new Obj->mem...会报错说->前缺少";", 应该使用(new Obj->mem), 但是此时要注意, 执行完内存就泄露了
// # 4 关于类中数据的初始化

#include <iostream>
#include <string>
using namespace std;
class ClassType
{
public:
	int i;
public:
	ClassType(int i) 
	{ 
		this->i = i; 
	}
	ClassType() { 
		//(*this)(9999);	// C++不支持构造函数调用另一个构造函数
		*this = ClassType(999);	// 这样替换java中的调用构造函数的方法试试
		cout << "\nmorengouzaohanshubeidiaoyong\n";
		cout << ClassType(333).i; 
	}
};

// # 4 关于类中数据的初始化
class T
{
public:
	int i;
	//int ii = 1;	// 不允许, java中允许
	//static int iii = 111;	// 不允许, java中允许
	const static int iiii = 1111;	// 允许
};

int main()
{
	// # 1
	/*int t = int();
	string str = "string";
	cout << str + t; */

	ClassType c;
	cout << c.i;

	// # 3 关于(new 对象)临时变量的方法调用的可行性	
	cout << "\n\n#3\n";
	cout << (new ClassType(20140915))->i << endl;

	// # 4 关于类中数据的初始化
	cout << "\n# 4 关于类中数据的初始化\n";
	T t;
	//cout << t.i << endl;// warning , rutime error 不能初始化
	cout << t.iiii << endl;
	cout << T::iiii << endl;
}