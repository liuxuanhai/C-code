// 程序清单 7.7
#include <stdio.h>
#include <ctype.h>
#define STOP '|'

int main(void)
{
	char c;
	char prev;         // 前一个读入的字符
	long n_chars = 0L; // 字符数
	int n_lines = 0;
	int n_words = 0;
	int p_lines = 0;   // 不完整的行数
	bool inword = false;
	                   // 如果c在一个单词中, 则inword设置成true

	printf ("Enter text to be analyzed ( | to terminate): \n");
	prev = '\n';       // 用于识别完整的行
	while (STOP != (c = getchar()))
	{
		n_chars++;
		if('\n' == c)
			n_lines++;
		if(!isspace(c) && !inword)
		{
			inword = true;
			n_words++;
		}
		if(isspace(c) && inword)
			inword = false;
		prev = c;
	}

	if(prev != '\n')
		p_lines = 1;

	printf("characters = %ld, words = %d, lines = %d, partial lines = %d\n", 
		n_chars, n_words, n_lines, p_lines);

	return 0;
}