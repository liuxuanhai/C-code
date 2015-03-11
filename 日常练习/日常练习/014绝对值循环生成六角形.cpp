#include <iostream>
#include <ctime>
#define JDZ(x) ((x) > 0 ? (x) : (-x))  // 绝对值宏定义
#define SEC 300  // 定义时间间隔(ms)

int x = 0, y = 0;
using namespace std;
void delay(void);

int main(void)
{
	int size = 15;
	while (1)
	{
		system("cls");
		for (y = 0; y <= size+5; y++, cout << '\n')
			for (x = -size; x <= size; x++)
			{
				if (JDZ(x) <= y && y <= size)
					cout << '*';
				else
					cout << ' ';
				if (y >= 5 && JDZ(x) <= size+5-y)
					cout << "\b*";
			}
		delay();

		system("cls");
		for (y = -(size - 5); y <= size - 5; y++, cout << '\n')
			for (x = 0; x <= size * 2 + 20; x++)
			{
				if (JDZ(y) <= x/3 && x <= 24)
					cout << '*';
				else
					cout << ' ';
				if (x >= 6 && JDZ(y) <= (size + 7 - x)/3 + 3)
					cout << "\b*";
			}
		delay();
	}

	return 0;
}

void delay(void)
{
	clock_t start, now;
	start = clock();
	while (1)
	{	
		if ((now = clock() - start) >= SEC)
			break;
		else
			cout << "\b\b\b\b" << SEC - now;
	}
}