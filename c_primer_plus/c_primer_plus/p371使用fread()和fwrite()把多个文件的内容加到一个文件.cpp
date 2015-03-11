// p371 程序清单 13.6 把多个文件的内容追加到一个文件中
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 1024         // 缓冲区大小     buffer 缓冲
#define SLEN 81              // 文件名称大小的限定

void append (FILE * source, FILE * dest);

int main (void)
{
	FILE * fa, * fs;         // fa指向目的文件, fs指向源文件
	int files = 0;           // 追加文件的个数
	char file_app [SLEN];    // 目的文件的名称
	char file_src [SLEN];    // 源文件的名称

	// 打开目的文件
	puts ("输入目的文件的名称:");
	gets (file_app);
	if (NULL == (fa = fopen (file_app, "a")))  // 追加写入模式
	{
		fprintf (stderr, "不能打开目的文件%s!\n", file_app);
		exit (2);
	}

	// 创建目的文件的缓冲区
	if (setvbuf (fa, NULL, _IOFBF, BUFSIZE) != 0)            // 成功执行返回0 否则非0
	{
		fputs ("不能创建缓冲区!\n", stderr);
		exit (3);
	}

	// 打开源文件
	puts ("输入第一个源文件的名称(空行结束).");
	while (gets (file_src) && file_src[0] != '\0')
	{
		if (strcmp (file_src, file_app) == 0)               // 比较源文件与目的文件名字是否相同
		{	
			fputs ("不能对文件本身进行追加!请重新输入\n", stderr);
			continue;
		}
		else if (NULL == (fs = fopen (file_src, "r")))
			fprintf (stderr, "不能打开%s文件!\n", file_src);
		else
		{
			if (setvbuf (fs, NULL, _IOFBF, BUFSIZE) != 0)  // 成功执行返回0 否则非0
			{
				fputs ("不能创建缓冲区!!", stderr);
				continue;
			}
			append (fs, fa);
			if (ferror (fs) != 0)
				fprintf (stderr, "读取%s源文件失败!\n", file_src);
			if (ferror (fa) != 0)
				fprintf (stderr, "写入%s目标文件失败!\n", file_app);
			fclose (fs);
			files++;
			printf ("源文件%s已经追加到了目标文件!\n", file_src);
			puts ("请输入下一个源文件(空行退出).");
		}
	}
	printf ("Done. %d files appended!\n", files);
	fclose (fa);

	return 0;
}

void append (FILE * source, FILE * dest)             // destination 目的
{
	size_t bytes;
	static char temp[BUFSIZE];                       // 分配一次

	while ((bytes = fread (temp, sizeof (char), BUFSIZE, source)) > 0)
		fwrite (temp, sizeof (char), bytes, dest);   // 将二进制数据写入文件
}