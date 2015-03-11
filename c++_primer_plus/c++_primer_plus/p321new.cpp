// 自己总结
#include <iostream>
int main()
{
	using namespace std;
// new initialization
	int * p1 = new int(10); // c++98
	cout << *p1 << endl;
	//int * p2 = new int{10}; // c++11 不支持
	//int * p3 = new int[3]{1, 2, 3}; // c++11 不支持

// new 失败
	// 1. 返回NULL // 2. std::bad_alloc
	
// ##### ????????? ##########
	//void * operator new(std::size_t); // p320

	return 0;
}