#include <iostream>
int main(void)
{
	using namespace std;
	cout << "\aOperation \"HyperHype\" is now activated!\n";
	cout << "Enter your agent code:____\b\b\b\b";
	long code;
	cin >> code;
	cout << "\aYou entered " << code << "...\n";
	cout << "\aCode verified! Proceed with Plan Z3!\n";
	cout << "可以用八进制或者十六进制表示字符如: \x41(hex), \101(oct)\n";

	return 0;
}