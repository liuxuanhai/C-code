// 程序清单 14.14
#include <stdio.h>
#include <stdlib.h>
#define MAXTITL 40
#define MAXAUTL 40
#define MAXBKS  5

struct book
{
	char title[MAXTITL];
	char author[MAXAUTL];
	double value;
};

int main(void)
{
	struct book library[MAXBKS];
	int count = 0;
	int index, filecount;
	FILE * pbook;
	int size = sizeof(struct book);

	// 二进制文件打开
	if (NULL == (pbook = fopen("p402book.dat", "a+b")))  // a+b 以追加的二进制形式打开文件, 以供读写
	{
		puts("Error: Can't open the file.");
		exit(EXIT_FAILURE);
	}
	// 读文件
	while (count < MAXBKS && fread(&library[count], size, 1, pbook))
	{
		if (count == 0)
			puts("文件内容如下:");
		printf("%s by %s values $%g.\n", library[count].title, library[count].author, library[count].value);
		count++;
	}
	filecount = count;
	if (count == MAXBKS)
	{
		puts("File Full!");
		exit(EXIT_FAILURE);
	}

	// 写进结构
	puts("请输入文件名(空行结束):");
	while (count < MAXBKS && gets(library[count].title)!= NULL && library[count].title[0] != '\0')
	{
		puts("Author:");
		gets(library[count].author);
		puts("Price:");
		scanf("%lf", &library[count++].value);
		while (getchar() != '\n')
			continue;
		if (count < MAXBKS)
			puts("Next file name(Empty line quit):");
		else
			puts("File Full");
	}
	// 写进文件
	if (count > 0)
	{
		puts("File book.dat content:");
		for (index = 0; index < count; index++)
			printf("%s by %s values $%g.\n", library[index].title, library[index].author, library[index].value);
		fwrite(&library[filecount], size, count - filecount, pbook);
	}
	else
		puts("No data.");
	puts("ok");
	fclose(pbook);

	return 0;
}