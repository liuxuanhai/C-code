// 建立		2013.12.13.19
// 复习		2014.08.15.11  # 1

// 以前当无法分配内存的时候, new返回一个空指针, 但是现在将会抛出异常, pt = new... pt相当于没有收到赋值, 因为new当中是throw出的异常, 根据栈解退直接跳到了try块的结尾, pt还是处于未初始化的状态, 如果不捕获这个异常, 执行状态下: abort()被调用 , 调试状态下: 指出了有一个未捕获的异常发生了, bad_alloc...   # 1
// 可以使用new (std::nothrow) Big[10000]指定使用返回nullptr的版本 # 1

#include <iostream>
#include <new>  // 包含了bad_alloc类的声明, 他是从exception类公有派生而来的
#include <cstdlib>
using namespace std;

struct Big
{
	double stuff[20000];
};

int main(void)
{
	Big * pb;

	if (new (std::nothrow) Big[10000] == nullptr)	// # 1
		cout << "可以使用new (std::nothrow) Big[10000]指定使用返回nullptr的版本\n\n";

	try
	{
		cout << "Trying to get a big block of memory:\n";
		pb = new Big[10000];  // 16 0000 0000 bytes
		cout << "Got past the new request:\n";
	}
	catch (bad_alloc & ba)	// 编译器生成临时副本, 然后引用临时副本 # 1
	{
		/*if (pb == nullptr)
			cout << "另一种标准是返回NULL\n";
		else
			cout << "另一种标准没打开\n";*/
		cout << "Caught the exception!\n";
		cout << ba.what() << endl;
		exit(EXIT_FAILURE);
	}
	catch(...)	// 加入编写了一个调用另一个函数的函数, 你并不知道被调用函数里面可能引发那些异常, 这时候仍然能够捕获异常, 方法是使用省略号来表示异常类型, 从而捕获任何异常 # 1
	{
		cout << "由于try块里面的函数之间的错综复杂的函数调用, 出现了未知的异常, 使用catch(...)捕获到了\n";
	}

	cout << "Memory successfully allocated\n";
	pb[0].stuff[0] = 4;
	cout << pb[0].stuff[0] << endl;
	delete [] pb;

	return 0;
}