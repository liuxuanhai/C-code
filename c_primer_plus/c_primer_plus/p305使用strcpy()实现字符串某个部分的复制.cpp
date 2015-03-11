// p305 ≥Ã–Ú«Âµ• 11.22
#include <stdio.h>
#include <string.h>
#define WORDS "BEST"
#define SIZE 40

int main (void)
{
	char * orig = WORDS;
	char copy[SIZE] = "Be the best you can be!";
	char * ps;

	puts (orig);
	puts (copy);
	ps = strcpy (copy + 7, orig);
	puts (copy);
	puts (ps);

	return 0;
}