// ´´½¨: 2014-08-28 13:48:57
#include "08Student.h"
#include <iostream>
using namespace std;
int main()
{
	Student stu("heshixiong");
	stu.getBaseInfo()["daxiong"] = "daxiong";
	cout << stu;
	cin >> stu;
	cout << stu;
}
