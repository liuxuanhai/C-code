// string版本的getline()将内容保存到对象的三种情况:
//		1. 到达文件结尾, 在这种情况下, 输入流的eofbit将被设置, 这意味着方法fail()和方法eof()都将返回true
//		2. 遇到分界字符(默认为\n), 在这种情况下, 讲吧分界字符从输入流中删除, 但是不储存他
//		3. 读取的字符数达到最大允许值(string::npos和可供分配的内存中较小的一个), 在这种情况下, 将会设置输入流的failbit, 这意味着方法fail()将返回true 
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
int main(void)
{
	using namespace std;
	ifstream fin;
	fin.open("p660从文件中读取字符串.txt");
	if (!fin.is_open())
	{
		cerr << "Can't open file. Bye.\n";
		exit(EXIT_FAILURE);
	}
	string item;
	int count = 0;
	getline(fin, item, ':');
	while (fin)
	{
		++count;
		cout << count << ": " << item << endl;
		getline(fin, item, ':');  // 在这里把默认的'\n'分界符换成了':' 所以在读取的时候会把'\n'也读进去
	}
	cout << "Done\n";
	fin.close();

	return 0;
}