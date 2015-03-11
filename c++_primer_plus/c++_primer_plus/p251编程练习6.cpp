// ±‡≥Ã¡∑œ∞ 7.13
#include <iostream>
const int Size = 5;
int fill_array(double ar[], int size);
void show_array(const double ar[], int size);
void change1_array(double *, int size);
void change2_array(double *, int size);

int main()
{
	double ar[Size];

	int size = fill_array(ar, Size);
	show_array(ar, size);
	std::cout << "After change1: " << std::endl;
	change1_array(ar, size);
	show_array(ar, size);
	std::cout << "After change2: " << std::endl;
	change2_array(ar, size);
	show_array(ar, size);

	return 0;
}

int fill_array(double * ar, int size)
{
	double temp = 0.0;
	int i = 0;
	std::cout << "#<" << size << "> - " << i << ": ";
	while (i < size && std::cin >> temp)
	{
		if (i < size - 1)
			std::cout << "#<" << size << "> - " << i + 1 << ": ";
		ar[i] = temp;
		i++;
	}

	return i;
}

void show_array(const double ar[], int size)
{
	for (int i = 0; i < size; i++)
		std::cout << ar[i] << std::endl;
}

void change1_array(double ar[], int size)
{
	double temp;
	for (int i = 1; 2 * i < size - 1; i++)
	{
		temp = ar[i];
		ar[i] = ar[size - 1 - i];
		ar[size - 1 - i] = temp;
	}
}

void change2_array(double ar[], int size)
{
	double temp;
	for (int i = 0, j = size - 1; i < j; i++, j--)
	{
		temp = ar[i];
		ar[i] = ar[j];
		ar[j] = temp;
	}
}