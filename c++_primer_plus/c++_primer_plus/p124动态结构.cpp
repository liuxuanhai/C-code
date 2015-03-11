// 编程练习 4.13 (8)
#include <iostream>
using namespace std;
#define SIZE 20

struct pissa
{
	char company[SIZE];
	float zhijing;
	float wigth;
};

int main()
{
	struct pissa * pissaPtr = new struct pissa;
	cout << "直径:\n";
	(cin >> pissaPtr->zhijing).get();
	cout << "公司名:\n";
	cin.getline(pissaPtr->company, SIZE);
	cout << "重量:\n";
	cin >> pissaPtr->wigth;

	cout << pissaPtr->company << endl
		<< pissaPtr->zhijing << endl
		<< pissaPtr->wigth << endl;

	return 0;
}