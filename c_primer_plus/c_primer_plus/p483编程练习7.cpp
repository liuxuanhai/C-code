// ≥Ã–Ú«Âµ• 16.17
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void showArray(const double ar[], int n);
double * new_d_array(int n, ...);

int main(void)
{

	double * p1;
	double * p2;

	p1 = new_d_array(5, 1.2, 2.3, 3.4, 4.5, 5.6);
	p2 = new_d_array(4, 100.0, 200.0, 8.08, -1890.0);
	showArray(p1, 5);
	showArray(p2, 4);
	free(p1);
	free(p2);

	return 0;
}

void showArray(const double ar[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%g ", ar[i]);
	puts("");
}

double * new_d_array(int n, ...)
{
	double * temp = (double *)malloc(sizeof(double) * n);
	va_list ap;
	va_start(ap, n);
	for (int i = 0; i < n; i++)
		temp[i] = va_arg(ap, double);
	va_end(ap);
	return temp;
}