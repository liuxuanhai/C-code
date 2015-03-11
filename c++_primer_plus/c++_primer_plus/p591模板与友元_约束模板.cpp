// 约束模板: 友元的类型取决于类被实例化的类型

#include <iostream>
using namespace std;
template <typename T> void counts();  // # 1/3 声明友元模板
template <typename T> void report(T &);

template <typename TT>
class HasFriendT
{
private:
	TT item;
	static int ct;  // 一种类型的所有对象使用一个ct
public:
	HasFriendT(const TT & i) : item(i) {ct++;}
	~HasFriendT() {ct--;}
	friend void counts<TT>();  // # 2/3 将模板声明为友元
	friend void report<>(HasFriendT<TT> &);  // 因为前面的友元模板声明中参数的类型与<>内的一致, 所以可以省略内部内容
};

template <typename T>
int HasFriendT<T>::ct = 0;

template <typename T>
void counts()
{
	cout  << "template size: " << sizeof(HasFriendT<T>) << "; ";
	cout  << "template counts(): " << HasFriendT<T>::ct << endl;
}

template <typename T>
void report(T & hf)
{
	cout <<hf.item << endl;
}

int main(void)
{
	counts<int>();
	HasFriendT<int> hfi1(10);
	HasFriendT<int> hfi2(20);
	HasFriendT<double> hfdb(10.5);
	report(hfi1);
	report(hfi2);
	report(hfdb);
	cout << "counts<int>() output:\n";
	counts<int>();
	cout << "counts<double>() output:\n";
	counts<double>();

	return 0;
}