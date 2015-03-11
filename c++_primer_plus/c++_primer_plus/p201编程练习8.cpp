// 编程练习 6.11 (8)
// 统计一个文件的字符数
#include <iostream>
#include <fstream>
#include <string>
int main()
{
	using namespace std;
	int count = 0;
	string filename;
	char ch;

	cout << "请输入要进行统计字符的文件的文件名:\n";
	cin >> filename;
	ifstream fin;
	fin.open(filename);
	if (!fin.is_open())
	{
		cout << "无法打开文件" << filename << endl;
		exit(EXIT_FAILURE);
	}
	while (fin >> ch)
	{
		cout << ch;
		count++;
	}
	cout << "一共有的字符数:" << count << endl << endl << endl;
	fin.close();
	fin.open(filename);
	if (!fin.is_open())
	{
		cout << "无法打开文件" << filename << endl;
		exit(EXIT_FAILURE);
	}
	count = 0;
	while (EOF != (ch = fin.get()))
	{
		cout << ch;
		count++;
	}
	cout << "一共有的字符数:" << count << endl << endl << endl;
	return 0;
}