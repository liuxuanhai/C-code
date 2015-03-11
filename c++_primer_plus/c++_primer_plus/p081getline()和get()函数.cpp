// 自己总结
#include <iostream>
int main()
{
	using namespace std;
	const int Size = 100;
	char ar1[Size];
	char ar2[Size];

	// getline()读取一行,并用空字符替换换行符
	// 由于cin.getline(ar1, Size)返回的是cin对象, 所以可以再在后面拼接一个getline();
	// 如果有大于等于Size个字符那么只能读取Size-1个字符, 然后getline()会将剩下的字符留在输入队列并设置失效位关闭输入;
	cout << "getline():\n";
	cin.getline(ar1, 10).getline(ar2, 10);
	cout << ar1 << endl << ar2 << endl;

	// get()读取一行, 但是他不读入换行符, 换行符会留在输入流中
	// get()如果没有参数, 那么他就跟getchar()一样可以读入一个字符, 即使下一个字符是换行符(利用的是函数重载)
	// get(ar1, size)返回的是一个cin对象, 但是cin.get()返回的不是一个对象
	cout << "get():\n";
	cin.get(ar1, Size).get();
	cin.get(ar2, Size);
	cin.get(); // 为下面的getline()开辟道路
	cout << ar1 << endl << ar2 << endl;

	// 检查遇到空行的时候两个函数的做法
	// getline()在前一条语句结束的位置开始读取(即读取空行)
	// get()读取空行后将设置失效位, 这意味着接下来的读取将会被阻断
	cout << "getline():\n";
	cin.getline(ar1, Size);
	cout << ar1 << endl;
	cout << "get():\n";
	cin.get(ar1, Size).get();
	cout << ar1 << endl;
	cin.get(ar2, Size);
	cout << ar2 << endl;

	return 0;
}