// 自己总结
/*static buding静态联编: 编译时给数组分配内存   dynamic buding动态联编: 在程序运行时创建数组(动态数组dynamic array)
静态数组 和 动态数组 的区别: .静态数组名是一个常量指针, 而动态数组名是一个变量指针
	. 静态数组名使用sizeof返回的是数组的字节数, 而动态的数组名使用sizeof返回的是指针的字节数原因是在这种情况下, 
	c和c++不会将常量指针解释为地址(另一个重要内容时对数组取地址的时候, 数组名也不会解释为其地址) */
#include <iostream>
int main()
{
	using namespace std;
	int in[10];
	int * in1Ptr = new int[10];

	cout << "静态数组名in使用sizeof:" << sizeof(in) << endl;
	cout << "动态数组名in1Ptr使用sizeof:" << sizeof(in1Ptr) << endl;

	short tell[10];
	short * tellPtr = new short[10];
	cout << "tell = " << tell << "直接使用的时候tell为数组第一个元素的地址" << endl;
	cout << "&tell = " << &tell << "对数组应用&运算符的时候得到的是整个数组的地址" << endl;
	cout << "tellPtr = " << tellPtr << "直接使用动态数组的数组名为第一个元素的地址" << endl;
	cout << "&tellPtr = " << &tellPtr << "对动态数组使用&运算符得到的是第一个元素的地址的地址" << endl;

	return 0;
}