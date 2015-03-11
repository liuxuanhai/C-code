// 程序清单 6.15
// 将输入显示到屏幕上和储存到文件中
#include <iostream>
#include <fstream>
int main()
{
	using namespace std;

	char automobile[50];
	int year;
	double a_price;
	double d_price;

	ofstream outFile;          // 创建ofstream类的对象
	outFile.open("p192文件输出.txt");// 把outFile同一个文件关联起来, 默认是没有就创建, 有就重新写入内容

	cout << "Enter the make and model of auto automobile: ";
	cin.getline(automobile, 50);
	cout << "Enter the model year: ";
	cin >> year;
	cout << "Enter the original asking price: ";
	cin >> a_price;
	d_price = 0.913 * a_price;

// display information on screen with cout

	cout << fixed; // 用一般方式输出浮点数而不是科学计数法
	cout.precision(2); // precision 准确度 准确的
	cout.setf(ios_base::showpoint);
	cout << "Make and model: " << automobile << endl;
	cout << "Year: " << year << endl;
	cout << "Was asking $" << a_price << endl;
	cout << "Now asking $" << d_price << endl;

// Now do exact same things using outFile instead of cout

	outFile << fixed;
	outFile.precision(2);
	outFile.setf(ios_base::showpoint);
	outFile << "Make and model: " << automobile << endl;
	outFile << "Year: " << year << endl;
	outFile << "Was asking $" << a_price << endl;
	outFile << "Now asking $" << d_price << endl;

	return 0;
}