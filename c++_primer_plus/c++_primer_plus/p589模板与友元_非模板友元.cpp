
// 本程序介绍非模板友元 此外还有约数(bound)模板友元 非约束(unbound)模板友元

#include <iostream>

using std::cout;
using std::endl;

template<class T>
class HasFriend
{
private:
	T item;
	static int ct;  // 每个类型的HasFriend都有自己的ct
public:
	HasFriend(const T & i) : item(i) {ct++;}
	~HasFriend() {ct--;}
	friend void counts();  // 所有类型共享的友元
	friend void reports(HasFriend<T> &);  // 属于单个类型的友元(因为参数所以他不是所有类型共享, 别的类型放上不能用, 是吧)  直接写HasFriend & 是不行的, 因为HasFriend不存在, 只存在各种类型的实例
	// 前面并没有template<typename T>说明他不是模板函数, 他只是一个使用一个模板做参数的函数, 这意味着必须为其进行显示具体化(因为没有编译指令template <>)
};

template<typename T>
int HasFriend<T>::ct = 0;

void counts()
{
	cout << "int count: " << HasFriend<int>::ct << "; ";
	cout << "double count: " << HasFriend<double>::ct << endl;
}

void reports(HasFriend<int> & hf)
{
	cout << "HasFriend<int>: " << hf.item << endl;
}

void reports(HasFriend<double> & hf)
{
	cout << "HasFriend<double>: " << hf.item << endl;
}

int main()
{
	cout << "No objects declared: ";
	counts();
	HasFriend<int> hfi1(10);
	cout << "After hfi1 declared: ";
	counts();
	HasFriend<int> hfi2(20);
	cout << "After hfi2 declared: ";
	counts();
	HasFriend<double> hfdb(10.5);
	cout << "After hfdb declared: ";
	counts();
	reports(hfi1);
	reports(hfi2);
	reports(hfdb);


	return 0;
}