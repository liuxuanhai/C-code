// 使用基类方法使用作用域解析符    (用类名显示的限定函数名不适合于友元函数, 因为友元函数不属于类)
// 使用基类对象本身使用强制类型转换
// 使用基类友元函数可以通过显示的转换为基类来调用正确的函数
#include "p544Has-a关系之私有继承_头文件.h"
using namespace std;

// public 函数
double Student::Average() const
{
	if (ArrayDb::size() > 0)  // 成员函数通过作用域解析符调用子对象的public函数
		return ArrayDb::sum()/ArrayDb::size();
	else
		return 0;
}

const string & Student::Name() const
{// 本方法返回一个引用, 该引用指向用于调用该方法对象的Student对象中的继承而来的string对象
	return (const string &)*this;  // 访问子对象本身使用强制类型转换可以满足
}

double & Student::operator[](int i)
{
	return ArrayDb::operator[](i);
}

double Student::operator[](int i) const  // const 类型的返回的时候如果不是const就不要引用直接创建临时变量就行了
{
	return ArrayDb::operator[](i);
}

// private 函数
ostream & Student::arr_out(ostream & os) const
{
	int i;
	int lim = ArrayDb::size();
	if (lim > 0)
	{
		for (i = 0; i < lim; i++)
		{
			os << ArrayDb::operator[](i) << " ";
			if (i % 5 == 4)
				os << endl;
		}
		if (i % 5 != 0)
			os << endl;
	}
	else
		os << " empty array ";
	return os;
}

// friend

// 使用string版本的operator>>()
istream & operator>>(istream & is, Student & stu)
{
	is >> (string &)stu;
	return is;
}

// 使用string friend getline(ostream &, const string &)
istream & getline(istream & is, Student & stu)
{
	getline(is, (string &)stu);
	return is;
}

// 使用string版本的operator<<
ostream & operator<<(ostream & os, const Student & stu)
{
	os << "Scores for " << (const string &)stu << ":\n";  // 通过类型转换来调用基类的友元函数
	stu.arr_out(os);  // 使用私有函数
	return os;
}