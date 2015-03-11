#include <stdio.h>
#include <string.h>
#define MAXTITL 40
#define MAXAUTL 40
#define MAXBKS  100     // 书的最大数量
struct book {
	char title[MAXTITL];
	char author[MAXAUTL];
	float value;
};

void sortt (struct book * pb[], int n); // sort 分类, 挑选
						// struct book * pb[] 结构指针数组
void sortv (struct book * pb[], int n);

int main (void)
{
	struct book library[MAXBKS];
	struct book * pbk[MAXBKS];         // 结构指针数组
	int count = 0;
	int index;

	puts ("输入书名:(空行结束)");
	while (count < MAXBKS && gets (library[count].title) != NULL
						  && library[count].title[0] != '\0')
	{
		puts ("输入作者:");
		gets (library[count].author);
		puts ("输入价格:");
		scanf ("%f", &library[count].value);
		pbk[count] = &library[count];
		count++;
		while (getchar () != '\n')
			continue;
		if (count < MAXBKS)
			puts ("输入书名:(空行结束)");
	}
	
	puts ("下面是书的列表:");
	for (index = 0; index < count; index++)
		printf ("%s by %s: $%.2f\n", library[index].title, library[index].author, 
		library[index].value);
	
	puts ("下面是按书名排序后书的列表:");
	sortt (pbk, count);
	for (index = 0; index < count; index++)
		printf ("%s by %s: $%.2f\n", pbk[index] -> title, (*(pbk[index])).author, 
		pbk[index] -> value);
	
	puts ("下面是按价格排序后书的列表:");
	sortv (pbk, count);
	for (index = 0; index < count; index++)
		printf ("%s by %s: $%.2f\n", pbk[index] -> title, (*(pbk[index])).author, 
		pbk[index] -> value);
	return 0;
}

void sortt (struct book * pb[], int n)  // 按照字符串排序 abcd...
{
	int top, search;
	struct book * temp;

	for (top = 0; top < n - 1; top++)
		for (search = top + 1; search < n; search ++)
			if (strcmp (pb[search] -> title, pb[top] -> title) < 0)
			{
				temp = pb[search];
				pb[search] = pb[top];
				pb[top] = temp;
			}
}

void sortv (struct book * pb[], int n)  // 按照价格由小到大排序
{
	int top, search;
	struct book * temp;

	for (top = 0; top < n - 1; top++)
		for (search = top + 1; search < n; search++)
			if (pb[search] -> value < pb[top] -> value)
			{
				temp = pb[search];
				pb[search] = pb[top];
				pb[top] = temp;
			}
}