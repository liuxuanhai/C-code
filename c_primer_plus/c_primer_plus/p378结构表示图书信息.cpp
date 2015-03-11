// p378 程序清单 14.1 结构
#include <stdio.h>
#define MAXTITL 41         // 书名的最大长度 + 1
#define MAXAUTL 31         // 作者的最大长度 + 1

struct book {              // 结构模板, 标记为book
	char title[MAXTITL];   // 书名
	char author[MAXAUTL];  // 作者
	float value;           // 价格
};                         // 结构模板结束

int main (void)
{
	struct book library;   // 把library声明为kook结构类型变量
	struct book chushihua = {
		"title",
		"author",
		1.23
	};

	puts ("请输入书名:");
	gets (library.title);  // 访问title部分
	puts ("请输入作者:");
	gets(library.author);  // 访问author部分
	puts("输入价格:");
	scanf ("%f", &library.value);
	printf ("%s by %s: $%.2f. \n", library.title, library.author, library.value);
	puts ("初始化的chushihua结构内容:");
	printf ("%s %s %f \n", chushihua.title, chushihua.author, chushihua.value);

	return 0;
}