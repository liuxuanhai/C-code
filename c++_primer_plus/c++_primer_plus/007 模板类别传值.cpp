// 创建: 2014-08-23 09:54:21
// template<int T>void print(int n)和void print2(int n)的类型一样
#include <iostream>

using namespace std;
typedef void (defType)(int);

template<int T>		// 如果这里明确声明了类型, 就可以print<2>传进一个值
void print(int n)
{
	cout << T << n << endl;
}

void print2(int n)
{
	cout << n << endl;
}

void print3(int n, int m)
{
	cout << "print3";
}

void ceshi(int n, defType f)
{
	f(n);
}

template<class fn>
void ceshi2(int n, fn f)
{
	f(n);
}

int main()
{
	print<2>(3);
	print2(4);

	// ceshi() 将第二个参数的类型牢牢限定为 void (__cdecl *)(int), 此时template<int T>void print(int n)是符合这个特征标的, 但是可以通过T穿进一个值
	ceshi(5, print2);
	//ceshi(5, print3);	// error C2664: “ceshi”: 不能将参数 2 从“void (__cdecl *)(int,int)”转换为“defType (__cdecl *)”
	ceshi(6, print<7>);
		// 但是print和print2的类型还是不相同的for_each()的第三个参数两种形式都认, 怎么实现的??????
		// 答案是把ceshi声明为
	ceshi2(6, print2);
	ceshi2(7, print<8>);
	//ceshi2(8, print3);	// 而通过模板定义的ceshi2则是无论什么类型都通吃, 但是内部调用上f(n)只使用了一个参数, 这儿限定了参数的数量
}