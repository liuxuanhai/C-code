// ±‡≥Ã¡∑œ∞ 4.13 (5)
#include <iostream>
#include <string>
using namespace std;

struct CandyBar
{
	string name;
	float weigth;
	int power;
};

int main()
{
	struct CandyBar sugar = {
		"HeShixiong",
		68.0,
		100
	};

	cout << sugar.name << endl
		<< sugar.weigth << endl
		<< sugar.power << endl;

	return 0;
}