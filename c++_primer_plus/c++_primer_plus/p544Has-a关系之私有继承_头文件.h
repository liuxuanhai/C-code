// 私有继承和包含的区别:
//     1. 包含版本提供两个被显示命名的对象成员, 私有继承提供了两个无名称的子类对象成员.
//     2. 成员初始化列表的时候包含使用对象名显示调用构造函数, 而私有继承使用类名加::调用
// 使用包含还是私有继承:
//	   通常应使用包含来建立has-a关系, 如果需要新类访问原有类的保护成员或需要重新定义虚函数, 则使用私有继承
#ifndef 程序清单14_4
#define 程序清单14_4
#include <iostream>
#include <string>
#include <valarray>

class Student : private std::string, private std::valarray<double>
{
private:
	typedef std::valarray<double> ArrayDb;
	//std::string name;  // 包含了一个对象
	//ArrayDb scores;    // 包含了另一个对象
	// 成绩输出的私有函数
	std::ostream & arr_out(std::ostream & os)const;
public:     // 显式调用了包含对象的构造函数
	Student(): std::string("Null Student"), ArrayDb() {}
	explicit Student(const std::string & s) : std::string(s), ArrayDb() {}  // 不允许隐式调用   一个参数的构造函数实现参数到类类型的类型转换 如果省略了explicit, 那么当出现Student d("Homer", 10); 这时候创建了一个对象, 对象的scores长度为10, 但是当把d[0]错写成d = 5;的时候, 会调用Student(5), 将5转换成一个临时的Student对象, 然后将临时对象赋值给d, 使得d的scores长度为5, string为Nully
	explicit Student(int n) : std::string("Nully"), ArrayDb(n) {}  // 不允许隐式调用
	Student(const std::string & s, int n) : std::string(s), ArrayDb(n) {}
	Student(const std::string & s, const ArrayDb & a) : std::string(s), ArrayDb(a) {}
	Student(const char * str, const double * pd, int n) : std::string(str), ArrayDb(pd, n) {}
	~Student() {}
	double Average() const;
	const std::string & Name() const;
	double & operator[] (int n);
	double operator[] (int n) const;
// 友元函数
	// 输入
	friend std::istream & operator>>(std::istream & is, Student & stu);
	friend std::istream & getline(std::istream & is, Student & stu);
	// 输出
	friend std::ostream & operator<<(std::ostream & os, const Student & stu);
};

#endif