// 编程练习 3
//利用数组 输入姓氏 名字 然后组合起来中间加一个逗号输出
#include <iostream>
#include <cstring>
#define SIZE 20
int main()
{
	using namespace std;
	char fir[SIZE];
	char sec[SIZE];
	char name[2 * SIZE + 1];
	char name_std[2 * SIZE + 1];

	cout << "First name:\n";
	cin >> fir;
	cout << "Second name:\n";
	cin >> sec;

	// #####自己的算法######
	strcpy(name, fir);
	name[strlen(fir)] = ',';
	strcpy(name + strlen(fir) + 1, sec);
	cout << "daxiong: " << name << endl;

	//########std算法#####
	strcpy(name_std, fir);
	strcat(name_std, ",");
	strncat(name_std, sec, SIZE); // sec中的前n个字符加到name结尾, 并且自动添加一个'\0'
							  // 如果sec不够n个字符则少的字符以'\0'代替
	cout << "std: " << name << endl;

	return 0;
}