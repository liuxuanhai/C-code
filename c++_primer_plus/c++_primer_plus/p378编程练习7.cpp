// ±‡≥Ã¡∑œ∞ 10.10 (7) 
#include <iostream>
#include "p378±‡≥Ã¡∑œ∞7.h"

int main()
{
	Plorg plorg1;
	Plorg plorg2("heshixiong");
	plorg1.show();
	plorg2.show();
	plorg1.change(1111);
	plorg2.change(2222);
	plorg1.show();
	plorg2.show();

	return 0;
}

Plorg::Plorg(const char * s, int n)
{
	strncpy(name, s, 19);
	name[19] = '\0';
	CI = n;
}
void Plorg::show() const
{
	std::cout << "Name: " << name << std::endl;
	std::cout << "CI: " << CI << std::endl;
}
void Plorg::change(int n)
{
	CI = n;
}