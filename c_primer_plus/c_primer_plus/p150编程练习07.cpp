#include <stdio.h>
int main(void)
{
	double a, b;

	while(2 == scanf("%lf%lf", &a, &b))
		printf("%lf", (a - b) / (a * b));

	return 0;
}