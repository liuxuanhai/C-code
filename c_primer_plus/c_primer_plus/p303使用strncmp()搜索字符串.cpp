// p 303 ≥Ã–Ú«Âµ• 11.20
#include <stdio.h>
#include <string.h>
#define LISTSIZE 5
#define FIND "astro"

int main (void)
{
	char * list[LISTSIZE] = {
		"astronomy", "astounding", 
		"astrophysics", "ostrisize",
		"asterism"};
	int count = 0;
	int i;

	for (i = 0; i < LISTSIZE; i++)
	{
		if (0 == strncmp(list[i], FIND, 5))
		{	
			count++;
			printf("find:%s\n", list[i]);
		}
	}

	printf ("This list contained %d words beginning with %s.\n", count, FIND);

	return 0;
}