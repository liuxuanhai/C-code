// p361 程序清单 13.3
#include <stdio.h>
#include <stdlib.h>
#define MAX 40
int main (void)
{
	FILE * fp;
	char words[MAX];

	if (NULL == (fp = fopen ("words.txt", "a+")))      // a+ 建立或打开一个可以读和写的文件, 如果文件已经存在, 则写入内容追加到文件尾部
	{
		fprintf (stdout, "不能打开\"words.txt\"文件!\n");
		exit (1);
	}
	puts ("输入要进行写入的内容, 通过在空行按enter结束.");
	while (gets (words) != NULL && words[0] != '\0')
		fprintf (fp, "%s", words);
	puts ("File contents:");
	rewind (fp);                                       // 回到文件的开始处
	while (fscanf (fp, "%s", words) == 1)
		puts (words);
	if (fclose(fp) != 0)
		fprintf (stderr, "无法关闭文件!\n");

	return 0;
}