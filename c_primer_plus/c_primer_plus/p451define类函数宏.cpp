// ≥Ã–Ú«Âµ• 16.2
#include <stdio.h>
#define SQUAER(X) X*X
#define PR(X) printf ("The result is %d.\n", X)

int main (void)
{
	int x = 4;
	int z;

	printf ("x = %d\n", x);
	z = SQUAER(x);
	printf ("Evaluating SQUARE(X): ");
	PR(z);
	z = SQUAER(2);
	printf ("Evaluating SQUARE(2): ");
	PR(z);
	printf ("Evaluating SQUARE(X+2): ");
	PR(SQUAER(x+2));
	printf ("Evaluating 100/SQUARE(2): ");
	PR(100/SQUAER(2));
	printf ("x is %d.\n", x);
	printf ("Evaluating SQUARE(++x): ");
	PR(SQUAER(++x));
	printf ("After incrementing, x is %x.\n", x);

	return 0;
}