// 程序清单 4.21
// new创建动态结构和用->访问动态结构
#include <iostream>
struct inflatable
{
	char name[20];
	float volume;
	double price;
};
int main()
{
	using namespace std;
	inflatable * ps = new inflatable;
	cout << "Name:\n";
	cin.get(ps->name, 20); // 读取一行内最大19个字符, 遇到换行符将停止读入, 把换行符留在输入流中
	cout << "Volume:\n";
	cin >> (*ps).volume;
	cout << "Price:\n$";
	cin >> ps->price;
	cout << "Name: " << ps->name << endl;
	cout << "Volume: " << ps->volume << endl;
	cout << "Price: $" << ps->price << endl;
	delete ps;

	return 0;
}