// 程序清单 5.17
#include <iostream>
int main()
{
	using namespace std;
	char ch;
	int count = 0;

	cout << "Enter characters; enter # to qiut:\n";
	// ### 有问题的算法 ####
	cin >> ch;
	while (ch != '#')
	{
		//cout << ch;
		++count;
		cin >> ch;
	}
	cout << "错误的统计出了:" << count << endl;

	// ### 正确的算法 ###
	cin.get(); // 把上个循环留在缓冲中的'\n'吃了
	count = 0;
	cin.get(ch); // 这里传递的是ch而不是ch的地址, 之所以能够修改ch的值是因为函数将参数声明为引用了
	while (ch != '#')
	{
		cout << ch;
		++count;
		cin.get(ch);
	}
	cout << "正确的统计出了:" << count << endl;

	return 0;
}