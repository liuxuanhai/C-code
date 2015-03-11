// 一个统计输入字数,行数,单词数的程序
// c primer plus 程序清单 7.7
// wordcnt.c -- 统计字符,单词和行
#include <stdio.h>
#include <ctype.h>                // 为isspace()提供函数原型
#define STOP '|'                  // 告诉程序输入结束
int main (void)
{
	char c;                       // 读入字符
	char prev;                    // STOP 前最后一个字符
	long n_char = 0L;             // 字符数
    int n_lines = 0;              // 行数
	int n_words = 0;              // 单词数
	int p_lines = 0;              // 不完整的行数
	int inword = 0;               // 标志

	printf ("Enter text to be analyzed (| to terminate): \n");
	prev = '\n';
	while ((c = getchar()) != STOP)// 如果为'|'则跳出循环
	{
		n_char++;                 // 字符数自增          //回车符也会当做一个字符加进去
		if (c == '\n')             // 判断行数
		{
			n_lines++;
		}
		if (!isspace (c)          // 如果读入的字符不是空格
			&& inword == 0)           // 标志为0 并且在读这个单词时一直保持0
		{
			inword = 1;
			n_words++;
		}
		if (isspace (c) && inword == 1)
		{
			inword = 0;
		}
		prev = c;
	}
	if (prev != '\n')
	{
		p_lines = 1;
	}
	printf ("characters = %ld, words = %d, lines = %d", n_char, n_words, n_lines);
	printf (" ,partial lines = %d\n", p_lines);
	return 0;
}