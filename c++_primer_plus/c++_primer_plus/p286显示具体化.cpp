// 程序清单 8.13
#include <iostream>
template <typename T>   // 函数模板
void Swap(T &a, T &b);

struct job
{
	char name[40];
	double salary;
	int floor;
};
template <> void Swap<job>(job &j1, job &j2);

inline void show(job &j); // 只能在函数生命的时候使用inline 只有一行代码的小型非递归函数适合作为内联函数

int main()
{
	using namespace std;
	cout.precision(2);
	cout.setf(ios::fixed, ios::floatfield);
	int i = 10, j = 20;
	cout << "i, j = " << i << ", " << j << ".\n";
	cout << "Using compiler-generated(编译-生成) int swapper:\n";
	Swap(i, j);   // generates void Swap(int &, int &);
		// 函数模板本身并不能生成函数定义
		// 但是使用int的模板实例是函数定义, 这种实例化方式称为隐式实例化
	cout << "Now i, j = " << i << ", " << j << ".\n";

	job sue = {"Susan Yaffee", 73000.60, 7};
	job sidney = {"Sidney Taffee", 78060.72, 9};
	cout << "Before job swapping:\n";
	show(sue);
	show(sidney);
	Swap(sue, sidney); // uses void Swap(job &, job &);
	cout << "After job swapping:\n";
	show(sue);
	show(sidney);

	return 0;
}

template <typename T>
void Swap(T &a, T &b) // general version
{
	T temp;
	temp = a;
	a = b;
	b = temp;
}

// swaps just the salary and floor fields of a job structure

template <> void Swap<job>(job &j1, job &j2)
{
	double t1;
	int t2;
	t1 = j1.salary;
	j1.salary = j2.salary;
	j2.salary = t1;
	t2 = j1.floor;
	j1.floor = j2.floor;
	j2.floor = t2;
}

void show(job &j)
{
	using namespace std;
	cout << j.name << ": $" << j.salary
		<< " on floor " << j.floor << endl;
}