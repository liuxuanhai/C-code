#include <stdio.h>  // rewind()
#include <stdlib.h>
#define FILENAME "p361word.txt"
int main(void)
{
	FILE * fp;
	char temp[100];

	if (NULL == (fp = fopen(FILENAME, "a+")))  // a+ 模式 可以读, 可以追加写, 没有文件将会创建文件
	{
		fprintf(stderr, "无法打开文件%s.\n", FILENAME);
		exit(EXIT_FAILURE);
	}

// 检测输入 将正确输入写入文件
	while (gets(temp) != NULL && temp[0] != '\0')  // EOF或空行终止程序
		fprintf(fp, "%s", temp);
	
// 将光标移动到文件开始处, 读取文件显示到stdout
	rewind(fp);
	fprintf(stdout, "File contents:\n");
	while (fscanf(fp, "%s", temp) == 1)
		puts(temp);  // 这里对于回车的控制十分的不好, 这更证明了fputs()和fgets()能够读取并将'\n'写入文件的必要性

// 将光标移动到文件开始出, 读取
	rewind(fp);
	while (fgets(temp, 100 ,fp) != NULL)
		fputs(temp, stdout);
	
	fprintf(stdout, "\nDone!");

	return 0;
}