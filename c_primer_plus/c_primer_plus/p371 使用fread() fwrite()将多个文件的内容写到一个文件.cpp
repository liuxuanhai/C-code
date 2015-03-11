#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 1024
#define SLEN 81

void append(FILE * dest, FILE * source);

int main(void)
{
	FILE * fa, * fs;  // fa指向目的文件, fs指向源文件
	int files = 0;
	char file_app[SLEN];
	char file_src[SLEN];
	char huanchong[BUFSIZE];

// 打开目的文件
	puts("输入目的文件的名称: ");
	gets(file_app);
	if (NULL == (fa = fopen(file_app, "a")))  // 追加写入模式
	{
		fprintf(stderr, "不能打开目的文件%s\n", file_app);
		exit(EXIT_FAILURE);
	}

	// int setvbuf(FILE * restrict fp, char * restrict buf, int mode, size_t size)创建目的文件的缓冲区  // setvbuf()建立供标准i/o函数使用的替换缓冲区, 打开文件以后, 在没有对流进行任何操作以前, 可以调用这个函数, 有指针fp来指定流, buf指向使用的存储区, 如果buf的值不是NULL, 就必须创建这个缓冲区(例如: 可以声明一个1024个字符的数组, 然后传递该数组的地址.), 但是, 如果buf的值是NULL, 函数会为自己自动分配一个缓冲区, size变量为setvbuf()函数指定数组的大小, mode将从下列选项中选取: _IOFBF表示完全缓冲(缓冲区满的时候刷新), _IOLBF表示行缓冲(缓冲区满的时候或者一个新行写入的时候刷新), _IONBF表示无缓冲 如果成功执行, 函数会返回零值, 否则返回非零值
	if (setvbuf(fa, huanchong, _IOFBF, BUFSIZE) != 0)  // 成功创建返回0
	{
		fputs("不能创建目的文件缓冲区", stderr);
		exit(EXIT_FAILURE);
	}

// 打开源文件
	puts("输入第一个源文件的文件名称(空行结束输入):");
	while (gets(file_src) && file_src[0])
	{
		if (!strcmp(file_app, file_src))
		{
			fputs("不能对文件本身进行追加, 请重新输入:\n", stderr);
			continue;
		}
		else if (NULL == (fs = fopen(file_src, "r")))
			fprintf(stderr, "不能打开%s文件!\n", file_src);
		append(fa, fs);
		if (ferror(fs) != 0)  // 如果最近一次输入调用发生的是读取错误而不是检测到了文件结尾, 函数返回一个非零值, 否则返回零值
			fprintf(stderr, "读取%s源文件失败!\n", file_src);
		if (ferror(fa) != 0)
			fprintf(stderr, "写入%s目标文件失败!\n", file_app);
		fclose(fs);
		files++;
		printf("huangchong: %s\n", huanchong);
		scanf("%s", huanchong);
		printf("源文件%s已经追加到了目标文件!\n", file_src);
		puts("请输入下一个源文件(空行退出):");
	}
	printf("Done. %d files appended!\n", files);
	fclose(fa);

	return 0;
}

void append(FILE * dest, FILE * source)
{
	size_t bytes;
	static char temp[BUFSIZE];

	while (bytes = fread(temp, sizeof(char), BUFSIZE, source))
		fwrite(temp, sizeof(char), bytes, dest);  // 将二进制数据写入文件
}