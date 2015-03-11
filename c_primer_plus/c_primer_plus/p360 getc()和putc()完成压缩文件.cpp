// 压缩文件为原来的1/3
#include <stdio.h>
#include <stdlib.h>  // exit()
#include <string.h>  // strrchr() strcpy() strcat()

int main(int argc, char * argv[])
{
	FILE * fp;
	FILE * fp2;
	char filename[100];
	int ch;
	int i = 0;

	if (argc != 2)
	{
		fprintf (stderr, "命令行输入错误\n");
		getchar();
		exit(EXIT_FAILURE);
	}
	
	if (NULL == (fp = fopen(argv[1], "r")))
	{
		fprintf (stderr, "不能成功打开文件%s\n", argv[1]);
		getchar();
		exit(EXIT_FAILURE);
	}

// 给压缩文件命名
	strcpy(filename, argv[1]);
	*strrchr(filename, '.') = '\0';
	strcat(filename, ".red.txt");

	if (NULL == (fp2 = fopen(filename, "w")))  // 同时也创建了压缩文件
	{
		fprintf (stderr, "不能成功打开文件%s\n", filename);
		getchar();
		exit(EXIT_FAILURE);
	}

	while (EOF != (ch = getc(fp)))
		if (0 == i++ % 3)
			putc(ch, fp2);

	if (0 != fclose(fp) || 0!= fclose(fp2))
	{
		fprintf(stderr, "不能关闭相关文件\n");
		getchar();
		exit(EXIT_FAILURE);
	}

	getchar();
	puts ("Done!");

	return 0;
}