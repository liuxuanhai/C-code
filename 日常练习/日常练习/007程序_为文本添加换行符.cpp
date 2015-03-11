// 指定一个文本每行最多的字符数, 自动完成换行
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define BYTE 75
#define SOURCE_F "007哈利波特和魔法石.txt"
#define GOAL_F "007哈利波特和魔法石_副本.txt"

FILE * openfile(char *, char *);
void r_and_w(FILE * source, FILE * total, int byte);
char * gett(FILE *, char *); // 自己写的读入函数

int main(void)
{
	FILE * source_f;
	FILE * goal_f;
	SetConsoleTitleA("by:大雄哥哥");

// 打开/创建文件
	if (source_f = openfile(SOURCE_F, "r"))
		goal_f = openfile(GOAL_F, "w");
	
	r_and_w(source_f, goal_f, BYTE);
	puts("ok!");

	return 0;
}

FILE * openfile(char * file, char * s)
{
	FILE * f;
	if ((f = fopen(file, s)) == NULL)
	{
		printf("Can't open the file \"%s\"!\n", file);
		getchar();
		exit(EXIT_FAILURE);
	}
	else
		printf("成功打开文件:%s\n", file);
	return f;
}

void r_and_w(FILE * source, FILE * goal, int byte)
{
	char ar[500];
	char temp[500];
	int i = 0;
	printf("开始处理");
	while (NULL != fgets(ar, 500, source))
	{
		while(ar[i])
			i++;
		printf("%d个字符:\n", i);
		printf("%s\n", ar);
		if (i > byte)
		{
			for (i = 0; i < byte; i++)
				temp[i] = ar[i];
			temp[i] = '\n';
			temp[i+1] = '\0';
			puts("分行转换完成.");
			fputs(temp, goal);
			fputs(&ar[i+1], goal);
			puts("成功写入副本!\n");
			i = 0;
		}
		else{
			puts("正在直接写入副本...");
			fputs(ar, goal);
			puts("直接写入副本成功!\n");
		}
		printf("开始处理:");
	}
}