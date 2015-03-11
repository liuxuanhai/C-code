// 程序清单 2.3
// 认识cin和cout
#include <iostream>

int main()
{
	using namespace std;

	int carrots;  // 胡萝卜

	cout << "How many carrots do you have?" << endl;
	cin >> carrots;
	cout << "Here are two more. ";
	carrots = carrots + 2;
	cout << "Now you have " << carrots << " carrots." << endl;

	return 0;
}