#include <iostream>
using namespace std;
#include "p531编程练习1_头文件.h"
void Bravo(const Cd & disk);

int main(void)
{
	Cd c1("Beatles", "Capitol", 14, 35.5);
	Classic c2 = Classic("Piano Sonata in b flat, Fantasia in C", "Alfred Brendel", "Philips", 2, 57.17);
	Cd * pcd = &c1;

	cout << "\nUsing object directly:\n";
	c1.Report();  // use Cd method
	c2.Report();  // use Classic method

	cout << "\nMsing type cd * pointer to objects:\n";
	pcd->Report();  // use Cd method for cd object

	pcd = &c2;
	pcd->Report();  // use Classic method for classic object

	cout << "\nCalling a function with a Cd reference";
	Bravo(c1);  // use Cd method for cd object
	Bravo(c2);  // use Classic method for classic object

	cout << "\nTesting assignment: ";
	Classic copy;
	copy = c2;
	copy.Report();

// 如果默认构造函数什么都不写的话会导致以下代码"烫烫烫烫烫..."   系统提供的默认构造函数函数体内什么也不写, 所以也会导致"烫烫烫烫烫..." 
	/*Classic cop;
	cop.Report();*/

	return 0;
}

void Bravo(const Cd & disk)
{
	disk.Report();
}