// 程序清单 4.11
#include <iostream>
struct inflatable   // structure declaration
{
	char name[20];
	float volume;
	double price;
};

int main()
{
	using namespace std;
	inflatable guest =
	{
		"Heshixiong",
		1.88,           // volume(体积) value
		29.99           // price value
	};
	inflatable pal = 
	{
		"Audacious Arthur",
		3.12,
		32.99
	};

	cout << "Expand(膨胀, 拓展) your guest list with " << guest.name;
	cout << " and " << pal.name << "!\n";
	cout << "You can have both for $";
	cout << guest.price + pal.price << "!\n";

	return 0;
}