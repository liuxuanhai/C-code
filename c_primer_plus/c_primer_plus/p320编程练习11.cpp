// ±‡≥Ã¡∑œ∞ 11.13 (11)
#include <stdio.h>
#include <ctype.h>
int main(void)
{
	char ar[91];
	int i = 0, B_N, L_N, W_N, Biaodian_N, Digit_N;
	int in_word;

	while (gets(ar))
	{
		i = 0;
		B_N = 0;
		L_N = 0;
		W_N = 0;
		Biaodian_N = 0;
		Digit_N = 0;
		in_word = 0;
		while (ar[i])
		{
			if (isdigit(ar[i]))
				Digit_N++;
			else if (ispunct(ar[i]))
				Biaodian_N++;
			else if (islower(ar[i]))
				L_N++;
			else if (isupper(ar[i]))
				B_N++;
			if (!isspace(ar[i]))
				in_word = 1;
			else if (in_word == 1 && isspace(ar[i]))
			{
				in_word = 0;
				W_N++;
			}
			i++;
		}
		if (in_word)
			W_N++;
		printf(" upper:%d\n lower:%d\n word:%d\n punct:%d\n digit:%d\n",
			B_N, L_N, W_N, Biaodian_N, Digit_N);
	}

	return 0;
}