// ±‡≥Ã¡∑œ∞14.18
#include <stdio.h>
#include <math.h>

double twice(double);
double half(double);
double thrice(double);
void showmenu(void);
#define NUM 4
int main(void)
{
	double (*pf[NUM])(double) = {twice, half, thrice, sqrt};
	double val;
	double ans;
	int sel;

	while (scanf("%lf", &val) && val >= 0)
	{
		showmenu();
		while (scanf("%d", &sel) && sel >= 0 && sel <= 3)
		{
			ans = (*pf[sel])(val);
			printf("answer = %f\n", ans);
			showmenu();
		}
		printf("Enter next number (negative to quit): ");
	}
	puts("Bye!");
	return 0;
}
void showmenu(void)
{
	puts("Enter one of the following choices:");
	puts("0> double the value   1> half the value");
	puts("2> thriple the value   3> squareroot the value");
	puts("4> next number");
}

double twice(double x){return 2.0 * x;}
double half(double x){return x / 2.0;}
double thrice(double x){return 3.0 * x;}