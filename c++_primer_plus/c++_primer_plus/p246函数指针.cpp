// 程序清单 7.19
#include <iostream>
const double * f1(const double ar[], int n);
const double * f2(const double [], int);
const double * f3(const double *, int);

int main()
{
	using namespace std;
	double av[3] = {1112.3, 1542.6, 2227.9};

	// 指向函数的指针
	const double *(*p1)(const double *, int) = f1;
	auto p2 = f2;      // c++11
	cout << "Using pointers to functiong:\n";
	cout << " Address Value\n";
	cout << (*p1)(av, 3) << ": " << *(*p1)(av, 3) << endl;
	cout << p2(av, 3) << ": " << *p2(av, 3) << endl;

	// 函数指针数组
	const double *(*pa[3])(const double *, int) = {f1, f2, f3};
	auto pb = pa;
	cout << "\nUsing an array of pointers to fuctions: \n";
	cout << " Address Value\n";
	for (int i = 0; i < 3; i++)
		cout << pa[i](av, 3) << ": " << *pa[i](av, 3) << endl;// 后边那个写成*(*pa[i])(av, 3)也行
	cout << "\nUsing a pointer to a pointer to a functiong:\n";
	cout << "Address Value\n";
	for (int i = 0; i < 3; i++)
		cout << pb[i](av, 3) << ": " << *(*pb[i])(av, 3) << endl;
	
	// 函数指针数组指针
	cout << "\nUsing pointer to an array of functiong pointers";
	cout << " Address Value\n";
	auto pc = &pa;   // &pa指的是整个数组的地址, &pa[0]和pa指的是数组第一个元素的地址, 两个指针数值虽然相同, 但是指向的数据不相同
	cout << (*pc)[0](av, 3) << ": " << *(*pc)[0](av, 3) << endl;
	const double *(*(*pd)[3])(const double *, int) = &pa;
	const double * pdb = (*pd)[1](av, 3);
	cout << pdb << ": " << *pdb << endl;
	cout << (*(*pd)[2])(av, 3) << ": " << *(*(*pd)[2])(av, 3) << endl;

	return 0;
}

const double * f1(const double * ar, int n)
{
	return ar;
}
const double * f2(const double ar[], int n)
{
	return ar + 1;
}
const double * f3(const double ar[], int n)
{
	return ar + 2;
}