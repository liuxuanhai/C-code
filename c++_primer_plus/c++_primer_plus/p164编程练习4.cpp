// ±‡≥Ã¡∑œ∞ 5.9
#include <iostream>
#define BENJIN 100
#define LILV_D 0.1
#define LILV_F 0.05
int main()
{
	double a = 0, b = BENJIN;
	int i = 1;
	do
	{
		a += BENJIN * LILV_D;
		b = b * LILV_F + b;
		i++;
	}while(a + BENJIN > b);
	std::cout << i << std::endl;

	return 0;
}