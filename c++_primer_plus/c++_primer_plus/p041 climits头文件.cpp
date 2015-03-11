// 在vs2012中都不用#include<climits>编译指令
#include <iostream>
using namespace std;
int main(void)
{
	cout << "CHAR_BIT : " << CHAR_BIT << endl;
	cout << "CHAR_MAX : " << CHAR_MAX << endl;
	cout << "CHAR_MIN : " << CHAR_MIN << endl;
	cout << "ULONG_MAX : " << ULONG_MAX << endl;
	cout << "ULLONG_MAX : " << ULLONG_MAX << endl;

	return 0;
}