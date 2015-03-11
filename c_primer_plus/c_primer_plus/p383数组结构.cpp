// p383 程序清单 14.2
#include <stdio.h>
#define MAXTITL 40
#define MAXAUTL 40
#define MAXBKS 100              // 最多可以容纳的图书册数

struct book {
	char title[MAXTITL];
	char author[MAXAUTL];
	float value;
};

int main (void)
{
	struct book libary[MAXBKS]; // book结构数组
	int count = 0;
	int index;

	puts ("请输入书名(空行退出):");
	while (count < MAXBKS && gets (libary[count].title) != NULL   // 如果gets ()试图越过文件结尾读取将会返回NULL
						  && libary[count].title[0] != '\0')      // gets ()不读入回车
	{
		puts ("输入作者:");
		gets (libary[count].author);
		puts ("输入价格:");
		scanf ("%f", &libary[count++].value);
		while (getchar () != '\n')                                // 如果输入123.00\n 由于scanf不会读入'\n' 所以'\n'会作为下次输入
			continue;          // 清空输入行
		if (count < MAXBKS)
			printf ("输入下一个书名:\n");
	}
	if (count > 0)
	{
		puts ("以下是书的目录:");
		for (index = 0; index < count; index++)
			printf ("%s by %s: $%.2f. \n", libary[index].title, 
					libary[index].author, libary[index].value);
	}
	else
		puts ("没有书!");

	return 0;
}