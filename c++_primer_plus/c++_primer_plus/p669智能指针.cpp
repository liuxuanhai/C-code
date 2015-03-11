// 创建: ‎2013‎年‎12‎月‎17‎日 ‏‎23:44:19
// 复习: 2014年08月19日 15:45:24 # 1

// 智能指针背后的思想: 不管是"忘记了"释放分配的内存还是异常导致的内存分配问题, 在函数结束后都会删除栈中的本地变量, 如果指针是一个对象的话, 就可以在析构函数中释放它指向的堆内存中的数据, 这样就实现了智能指针... # 1
// 注意: 不要把非堆内存地址传给智能指针, 智能指针的复制转换构造函数是explicit的; # 1
// 关于防止多个智能指针删除同一个堆内存多次的策略:
	// 1. 定义赋值运算符, 执行深复制;
	// 2. 建立所有权(ownership)概念, 对于特定的对象, 只有一个智能指针可以拥有它, 只有拥有对象的智能指针的析构函数能够删除该对象.	 赋值操作会转让所有权.	这个是auto_ptr和unique_ptr的策略, 但是unique_ptr的策略更严格(严格在unique_ptr只允许"="右边是一个临时右值unique_ptr对象);	注意(缺陷): 失去所有权意味着将不再指向堆中的特定内存;
	// 3. 创建智能更高的指针, 跟踪引用特定对象的智能指针数, 这称为引用计数, 仅当最后一个指针对象过期的时候, 才调用delete, 这是shared_ptr的策略;
// 关于new[]
	// 1. 不能使用auto_ptr和shared_ptr了
	// 2. 可以使用unique_ptr std::unique_ptr<double[]>pda(new double(5)); // will use delete [] # 1

#include <iostream>
#include <string>
#include <memory>	// # 1 提供智能指针类

class Report
{
private:
	std::string str;
public:
	Report(const std::string s) : str(s) {std::cout << "Object created!\n";}
	~Report() {std::cout << "Object deleted!\n";}
	void comment() const {std::cout << str << "\n";}
};

int main(void)
{
	{
		std::auto_ptr<Report> ps (new Report("Using auto_ptr"));
		ps->comment();
	}
	{
		std::shared_ptr<Report> ps (new Report("using shared_ptr"));
		ps->comment();
	}
	{
		std::unique_ptr<Report> ps (new Report("using unique_ptr"));
		ps->comment();
	}

	return 0;
}