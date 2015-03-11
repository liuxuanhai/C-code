// p360 程序清单 13.2
// 通过保留每三个字符中的第三个把文件压缩为原来的三分之一
#include <stdio.h>
#include <stdlib.h>      // 为了调用exit();
#include <string.h>      // 为strcpy()和strcat()函数提供原型
#define LEN 1000

int main (int argc, char * argv[])
{
	FILE * in, * out;    // 声明两个file指针
	int ch;
	char name[LEN];      // 用于储存输入的文件名
	int count = 0;
	// 检查命令行参数
	if (argc < 2)
	{	
		fprintf (stderr, "未能成功给%s指定文件!\n", argv[0]);
		
		exit (EXIT_FAILURE);
	}

	// 实现输入
	if ((in = fopen (argv[1], "r")) == NULL)
	{
		fprintf (stderr, "我不能打开\"%s!\"\n", argv[1]);
		system("pause");
		exit (EXIT_FAILURE);
	}

	// 创建压缩文件
	strncpy (name, argv[1], strlen (argv[1]) - 4);      // 把文件名复制到数组中
	name[strlen (argv[1]) - 4] = '\0';                  // 注意name[4]实际是第五个元素!!!!!!!!!!!!!!!!!!
	strcat (name, ".red.txt");   // 给文件名后加.red    // strcat会用.把name中的第一个'\0'替换掉 并给最后加上'\0'
	printf (name);
	if ((out = fopen (name, "w")) == NULL)
	{
		fprintf (stderr, "不能创建压缩文件!\n");
		system("pause");
		exit (EXIT_FAILURE);
	}

	// 复制数据
	while ((ch = getc(in)) != EOF)
		if (count++ % 3 == 0)
			putc (ch, out);  // 打印每三个字符中的一个

	// 收尾工作
	if (fclose(in) != 0 || fclose (out) != 0)
		fprintf (stderr, "无法关闭相关文件!\n");

	return 0;
}