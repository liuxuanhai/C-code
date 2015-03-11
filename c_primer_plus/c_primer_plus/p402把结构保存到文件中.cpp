// p402 程序清单 14.14
#include <stdio.h>
#include <stdlib.h>
#define MAXTITL 40
#define MAXAUTL 40
#define MAXBKS  5

struct book {
	char title[MAXTITL];
	char author[MAXAUTL];
	float value;                      // !!!!!!!!!!!!!!这里写成double是不对的!!!!!!!!!!!!!!!!!!!!
};

int main (void)
{
	struct book library[MAXBKS];                      // 结构数组
	int count = 0;
	int index, filecount;
	FILE * pbook;
	int size = sizeof (struct book);

	// 二进制打开文件
	if (NULL == (pbook = fopen ("p402book.dat", "a+b")))  // a+b 以二进制建立或打开一个可供读和写的文件如果文件已经有内容, 则添加到文件尾部
	{
		puts ("无法打开文件!");
		exit (EXIT_FAILURE);
	}
	// 读文件
	rewind (pbook);                                   // 定位到开始处
	while (count < MAXBKS && fread (&library[count],
									size, 1, pbook))
	{
		if (count == 0)
			puts ("文件的内容如下:");
		printf ("%s by %s values $%g.\n", library[count].title, 
						library[count].author, library[count].value);
		count++;
	}
	filecount = count;
	if (count == MAXBKS)
	{
		puts ("文件已经满了!");
		exit (EXIT_FAILURE);
	}

	// 写进结构
	puts ("请输入文件名(空行结束):");
	while (count < MAXBKS && (gets (library[count].title) != NULL)
						  && (library[count].title[0] != '\0'))
	{
		puts ("输入作者:");
		gets (library[count].author);
		puts ("输入价格:");
		scanf ("%f", &library[count++].value);
		while (getchar() != '\n')
			continue;
		if (count < MAXBKS)
			puts ("输入下一个书名(空行结束):");
		else
			puts ("文件已经满了,不能在进行输入!!!");
	}

	// 写进文件
	if (count > 0)
	{
		puts ("下面是book.dat的内容:");
		for (index = 0; index < count; index++)
			printf ("%s by %s values $%g.\n", library[index].title, 
							library[index].author, library[index].value);
		fwrite (&library[filecount], size, count - filecount, pbook);
	}
	else
		puts ("没有书.");
	
	// 结尾
	puts ("ok!");
	fclose (pbook);

	return 0;
}