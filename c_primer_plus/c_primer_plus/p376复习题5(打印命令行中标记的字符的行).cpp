// ∏¥œ∞Ã‚ 13.10 (5)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[])
{
	FILE * fp;
	char temp[999];

	if (argc != 3)
	{
		fprintf(stderr, "Usage: [%s] [char] [filename]", argv[0]);
		getchar();
		exit(EXIT_FAILURE);
	}
	if (NULL == (fp = fopen(argv[2], "r")))
	{
		fprintf(stderr, "Can't open %s.\n", argv[2]);
		getchar();
		exit(EXIT_FAILURE);
	}
	while (fgets(temp, 999, fp))
		if (strchr(temp, argv[1][0]))
			fputs(temp, stdout);

	getchar();
	puts("Done!");

	return 0;
}