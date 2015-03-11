#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "daxiong.h"

void wait (double);
void random_pick (int ar[], int arsize, int picks);

#define SPORTS 51
#define PICKS  6

int main (void)
{
	int lotto[SPORTS];
	int i;
	char ch;

	for (i = 0; i < SPORTS; i++)
		lotto[i] = i + 1;
	do {
		random_pick (lotto, SPORTS, PICKS);
		printf ("Again? <y / n>");
		ch = getchar ();
		eatline();
	} while ('y' == ch || 'Y' == ch);
	puts ("Done!");

	return 0;
}

void random_pick (int ar[], int arsize, int picks)
{
	int i, index, temp;

	srand (time(0));
	if (picks > arsize)
	{
		fputs ("Number of picks > array size\n", stderr);
		fputs ("Setting picks = array size\n", stderr);
		picks = arsize;
	}
	for (i = 0; i < picks; i++)
	{
		index = rand () % (arsize - 1);
		temp = ar[index];
		printf ("%2d ", temp);
		if (i % 20 == 19)
			putchar ('\n');
		ar[index] = ar[arsize - 1];
		ar[arsize - 1] = temp;
		arsize--;
	}
	if (i % 20 != 0)
		putchar ('\n');
}