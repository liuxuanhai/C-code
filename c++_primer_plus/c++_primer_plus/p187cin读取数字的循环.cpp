// 创建: ‎2013‎-0‎7-‎18‎ 0‏‎6:01:50
// 复习: ‎2014-08-27 21:13:33  cin的错误标记恢复: cin.clear()
// 程序清单 6.13
// 如果用户输入一个单词而不是数字给 int i; cin >> i;那么会产生四中后果:
// .i的值不会改变
// .不匹配的输入将被留在输入队列中
// .cin对象中的一个错误标记被设置
// .对cin方法的调用会返回false(如果被转换为bool类型)
// ##### 注意 ####
// 非数字输入设置错误标记意味着必须重置该标记, 程序才能继续用cin对象读取输入
// clear()方法重置输入错误标记, 同时也重置文件尾EOF.
#include <iostream>
const int Max = 5;
int main()
{
	using namespace std;
	double fish[Max];
	cout << "Please enter the weights of your fish.\n";
	cout << "You may enter up to " << Max
		<< " fish <q to terminate>.\n";
	cout << "fish #1: ";
	int i = 0;
	while (i < Max && cin >> fish[i])
		if (++i < Max)
			cout << "fish #" << i + 1 << ": ";
	double total = 0.0;
	for (int j = 0; j < i; j++)
		total += fish[j];
	if (0 == i)
		cout << "No fish\n";
	else
		cout << total / i << " = average weight of "
			<< i << " fish\n";
	cout << "Done.\n";
	cin.get();cin.get();cin.get();
	cin >> i;
	scanf ("%c", &i); // 虽然cin对象不能使用了 但是scanf()一样可以读取输入的
	cout << "scanf():" << i << endl;
	cin.clear();
	cin >> i;
	cout << "cin:" << i << endl;

	return 0;
}