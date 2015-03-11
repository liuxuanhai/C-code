// 程序清单 3.4
// cout输出八进制和十六进制 控制符:dec十进制 oct八进制 hex十六进制
#include <iostream>
using namespace std;
int main()
{
	using namespace std;
	int chest = 42;
	int waist = 42;
	int inseam = 42;

	cout << "Monsieur(先生 磨er修er) cuts a striking(引人瞩目的) figure(数字,算术)!" << endl;
	cout << "十进制chest = " << chest << endl;
	cout << hex;  // 控制符实际上是一条消息, 告诉cout采取何种行为;
	cout << "十六进制waist = " << waist << endl;
	cout << oct;
	cout << "八进制inseam = " << inseam << endl;

	return 0;
}