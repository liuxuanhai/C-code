// 1. 名称空间只能在非代码区, 所以他的链接性默认为外部(除非它引用了常量);
// 2. 名称空间是开放的, 可以在不同文件将变量放在统一名称空间;
// 3. using namespace Jill; 是编译指令, 编译器自动为变量前面加上Jill::, 然而using Namespace::n;进行声明的时候, 就好像声明了相应的名称一样, 这样再声明局部变量int n的时候出现了重定义的错误;
#include <iostream>
using namespace std;

namespace Jill{
	double bucket(double n){return n;};
	double fetch;
	struct Hill{
		int a;
		int b;
	};
};

namespace Namespace{
	int n;
};

char fetch;  // 全局变量

int main(void)
{
	using namespace Jill;			// 导入所有空间名
	Hill Thrll;						// 创建结构体: Jill::Hill
	double water = bucket(2);		// 使用Jill::bucket();
	double fetch;					// 没有错, 隐藏了Jill::fetch;  // 这里不会导致重定义的错
	cin >> fetch;					// local fetch
	cin >> ::fetch;					// global fetch
	cin >> Jill::fetch;				// Jill::fetch

	using Namespace::n;				// 这里将会报出重定义的错
	int n;
	cin >> n;

	return 0;
}

int foom()
{
	//Hill top;  // Error
	Jill::Hill create;		// valid
}