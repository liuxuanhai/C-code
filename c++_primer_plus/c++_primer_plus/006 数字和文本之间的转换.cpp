// 创建: 2014-08-22 14:47:01
// atoi() itoa() sprintf() sscanf()

#include <iostream>
#include <string>
using namespace std;
#pragma warning(disable: 4996)
int main()
{
	//============= 文本 => 数字 ==============
				
				// atoi()

	string str1 = "18 : 56";
	cout << str1 << " = " << atoi(str1.c_str()) << endl;	// 输出18

				// sscanf()

	int temp1;
	int temp2;
	sscanf(str1.c_str(), "%d : %d", &temp1, &temp2);
	cout << str1 << " = \n\ttemp1 = " << temp1 << "\n\ttmep2 = " << temp2 << endl << endl;

	//============= 数字 => 文本 ==============

				// itoa()

	temp1 = 123456;
	char tmp[32];
	cout << temp1 << " = " << itoa(temp1, tmp, 10) << " dec" << endl;	// 第二个参数是必须的, nullptr会导致写入0x00000000发生访问冲突
	cout << temp1 << " = " << itoa(temp1, tmp, 2) << " bin" << endl;	// 二进制
	cout << temp1 << " = " << itoa(temp1, tmp, 8) << " oct"<< endl;		// 八进制
	cout << temp1 << " = " << itoa(temp1, tmp, 16) << " hex"<< endl << endl;	// 十六进制
				// ssprintf()

	sprintf(tmp, "%d", temp1);
	cout << temp1 << " = " << tmp << " dec" << endl;	// 十进制
	//cout << temp1 << " = " << temp1 << " bin" << endl;	// 二进制
	sprintf(tmp, "%o", temp1);
	cout << temp1 << " = " << tmp << " oct"<< endl;		// 八进制
	sprintf(tmp, "%x", temp1);
	cout << temp1 << " = " << tmp << " hex"<< endl;	// 十六进制

	/*int x = 100;
	printf ("十进制: %d, 八进制: %o, 十六进制: %x(%X)\n", x, x, x, x);
	printf ("十进制: %d, 八进制: %#o, 十六进制: %#x(%#X)\n", x, x, x, x);*/
}