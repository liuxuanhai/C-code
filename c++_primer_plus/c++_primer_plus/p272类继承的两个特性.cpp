// 程序清单 8.8
// 特性: 1. 派生类可以使用基类的特性 2. 基类引用可以指向派生类对象而无需进行强制类型转换
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

void file_it(ostream & os, double fo, const double fe[], int n);
const int LIMIT = 5;
int main()
{
	ofstream fout;
	const char * fn = "p272显微镜资料.txt";
	fout.open(fn);
	if (!fout.is_open())
	{
		cout << "Can't open " << fn << ". Bye!";
		exit(EXIT_FAILURE);
	}
	double objective;
	cout << "Enter the focal length of your "
		"telescope objective in mm: ";
	cin >> objective;
	double eps[LIMIT];
	cout << "Enter the focal length, in mm, of " << LIMIT << " eyepieces:\n";
	for (int i = 0; i < LIMIT; i++)
	{
		cout << "Eyepiece #" << i + 1 << ": ";
		cin >> eps[i];
	}
	file_it(fout, objective, eps, LIMIT);
	file_it(cout, objective, eps, LIMIT);
	cout << "Done\n";

	return 0;
}

void file_it(ostream & os, double fo, const double fe[], int n)
{
	ios_base::fmtflags initial;
	initial = os.setf(ios_base::fixed); // setf()能够让我设置各种格式换状态 setf(ios_base::fixed)将对象置于使用定点表示法模式下
			// setf()返回调用它之前的格式化设置 ios_base::fmtflags 是储存这种信息需要的数据类型名称
	os.precision(0); // precision 精确度 定点模式下: 指定显示多少位小数
	os << "Focal length of objective: " << fo << " mm\n";
	//os.setf(ios::showpoint); // setf(ios::showpoint) 将对象置于显示小数点的模式, 即小数部分为0
	os.precision(1);

	// 以上的格式化设置都将保持不变, 直到再次调用相应的方法重新设置他们

	os.width(12); // 设置下一次输出操作使用的字段宽度, 只在显示下一个值的时候有效, 然后恢复到默认设置0
	os << "f.1. eyepiece";
	os.width(15);
	os << "magnification" << endl;
	for (int i = 0; i < n; i++)
	{
		os.width(12);
		os << fe[i];
		os.width(15);
		os << int (fo/fe[i] + 0.5) << endl;
	}
	os.setf(initial);
}