// 程序清单 5.19
#include <iostream>
int main()
{
	using namespace std;
	int ch;  // 这里声明的是int不是char哦
	int count = 0;

	while (EOF != (ch = cin.get())) // 因为cin.get()能够读取EOF(-1)所以他的返回值为int类型, 但是有的系统char的类型可能为unsigned所以使用int来声明ch;
	{
		cout.put(char(ch));  // char(ch) 将ch的类型显示的转换成char类型, 因为ch前面生命的是int类型, 然后在有些c++的实现中有三个原型put(char);put(unsigned char);put(signed char)所以在使用put(int);的时候隐式的转换将不会知道到底转换成什么类型
		++count;
	}
	cout << endl << count << " characters read\n";
	cin >> ch;   // 如果进行的是 启动调试 而不是 开始执行(不调试) 那么在最后dos框会一闪而过, 即使后面有cin >> ch;也不行, 因为在检测到了EOF以后将会禁止进一步输入所以这里只能有其他的两个方案 . 使用延时循环 . 使用cin.clear();重置输入流

	return 0;
}