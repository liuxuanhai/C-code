// 自己总结
// 关于指针未初始化的危险
#include <iostream>
int main()
{
	using namespace std;
	int * inputPtr;   // 声明一个指针, 分配指针的内存空间
					  // 但是他没有初始化, 所以并没有给指针指向的int分配内存空间
	*inputPtr = 222;  // 222将会不知道放在哪里
	cout << inputPtr << endl;

	return 0;
}