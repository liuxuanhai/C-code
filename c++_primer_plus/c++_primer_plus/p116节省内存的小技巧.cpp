// 程序清单 4.22
// 通过创建临时数组 然后动态分配数组使用的内存大小来动态分配内存 以达到节省内存的目的
#include <iostream>
#include <cstring>
using namespace std;
char * getname(void);
int main()
{
	char * name;

	name = getname();
	cout << name << " at " << (int * )name << endl;
	delete [] name; // 把delete和new放在不同的函数中不是一个好的做法, 这里只是为了告诉你这样做是可以的

	return 0;
}
char * getname() // 此处可以省写void
{
	char temp[80];
	cout << "Enter last name: " << endl;
	cin >> temp;
	char * pn = new char[strlen(temp) + 1];
	strcpy(pn, temp);

	return pn;
}