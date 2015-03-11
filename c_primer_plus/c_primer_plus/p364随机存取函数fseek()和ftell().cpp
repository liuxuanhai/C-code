// p364 程序清单 13.5
#include <stdio.h>
#include <stdlib.h>
#define CNTL_Z '\032'    // dos文本文件的文件结尾标记
	// 二进制形式的时候EOF(Ctrl+z)会被当做字符读取, 不能作为结束的标记
#define SLEN 50
int main (void)
{
	char file[SLEN];     // 用于储存文件名
	char ch;
	FILE * fp;
	long count, last;

	puts ("请输入要进行测试的文件名:");     // Microsoft Visual C++ 会在源文件文件夹中寻找文件
	gets (file);

	// 打开文件
	if ((fp = fopen (file, "rb")) == NULL)  // rb 以二进制形式打开一个供读取的文件
	{
		puts ("不能打开指定文件!");
		exit (1);
	}

	// 对文件进行随机存取
	fseek (fp, 0L, SEEK_END);               // 定位到文件结尾处  正常执行返回0 异常返回-1
	last = ftell (fp);                      // ftell()通过返回距离文件开始出的字节数来确定文件的位置(适用于用二进制打开的文本, 对于以文本模式打开的文件来讲不一定适用)
	for (count = 1L; count <= last; count++)
	{
		fseek (fp, -count, SEEK_END);       // 回退
		ch = getc (fp);
		// 针对dos 在unix下也可以工作
		if (ch != CNTL_Z && ch != '\r')
			putchar (ch);
	}
	
	// 关闭文件
	putchar ('\n');
	fclose (fp);

	return 0;
}