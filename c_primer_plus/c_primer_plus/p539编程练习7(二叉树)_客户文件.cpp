// 编程练习 17.12
#include <stdio.h>
#include <stdlib.h>
#include "p539编程练习7(二叉树).h"
#define FILENAME "p539编程练习7(二叉树).txt"

enum CHOICE {show, find, quit};

int GetChoice();
void ShowTree(Node *);
Item GetItem();

int main(void)
{
	FILE * fp;
	Tree Words;
	Item temp;
	
	if (NULL == (fp = fopen(FILENAME, "r")))
	{
		fprintf(stderr, "Can't open the file.\n");
		exit(1);
	}
	puts("成功打开文件...");
	Ini(&Words);
	puts("成功初始化树...");
	while (fscanf(fp, "%s", temp.wrd) == 1)
		AddItem(&temp, &Words);
	puts("成功将数据读入树内...");
	
	int choice = GetChoice();
	Node * pn;
	switch (choice)
	{
	case show:
		Travel(&Words, ShowTree);
		break;
	case find:
		if (pn = IsInTree(&GetItem(), &Words))
			printf("%s : %d\n", pn->item.wrd, pn->count);
		else
			puts("不在树里面");
		break;
	case quit:
		break;
	default:
		puts("Switch Error!");
	}
	
	fclose(fp);

	return 0;
}

static void ShowTree(Node * pn)
{
	printf("%s : %d\n", pn->item.wrd, pn->count);
}

int GetChoice()
{
	int ch;
	puts("1> 列出所有单词及出现次数   2> 查找单词   3>退出");
	ch = getchar();
	if (ch == '1')
		return show;
	else if (ch == '2')
		return find;
	else if (ch == '3')
		return quit;
	else
	{
		puts("输入错误");
		exit(1);
	}
}

Item GetItem()
{
	Item temp;
	while (getchar() != '\n');
	puts("请输入一个单词: ");
	gets(temp.wrd);
	return temp;
}