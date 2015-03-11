// ±‡≥Ã¡∑œ∞ 13.11 (11) ª≠Õº
#include <stdio.h>
#include <stdlib.h>
#define ROWS 20
#define COLS 30
#define LEVELS 10

const char trans[LEVELS + 1] = " .':~*=&%@";

void MakePic(int data[][COLS], char pic[][COLS], int rows);
void init(char arr[][COLS], char ch);

int main(void)
{
	int row, col;
	int picIn[ROWS][COLS];
	char picOut[ROWS][COLS];
	char fileName[40];
	FILE * infile;

	init(picOut, 's');

	printf("Enter name of file: ");
	scanf("%s", fileName);
	if (NULL == (infile = fopen(fileName, "r")))
	{
		fprintf(stderr, "Could not open data file.\n");
		exit(EXIT_FAILURE);
	}

	for (row = 0; row < ROWS; row++)
		for (col = 0; col < COLS; col++)
			fscanf(infile, "%d", &picIn[row][col]);
	if (ferror(infile))
	{
		fprintf(stderr, "Error getting data from file.\n");
		exit(EXIT_FAILURE);
	}
	MakePic(picIn, picOut, ROWS);

	for (row = 0; row < ROWS; row++)
	{
		for (col = 0; col < COLS; col++)
			putchar(picOut[row][col]);
		putchar('\n');
	}

	return 0;
}

void init(char arr[][COLS], char ch)
{
	int r, c;
	for (r = 0; r < ROWS; r++)
		for (c = 0; c < COLS; c++)
			arr[r][c] = ch;
}

void MakePic(int data[][COLS], char pic[][COLS], int rows)
{
	int row, col;
	for (row = 0; row < rows; row++)
		for (col = 0; col < COLS; col++)
			pic[row][col] = trans[data[row][col]];
}