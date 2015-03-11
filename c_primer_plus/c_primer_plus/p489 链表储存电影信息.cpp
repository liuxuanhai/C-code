// 程序清单 17.2
#include <stdio.h>
#include <stdlib.h>  // malloc()
#include <string.h>  // strcpy()
#define TSIZE 75  // Movie title limit

struct film
{
	char title[TSIZE];
	int rating;
	struct film * next;
};

int main(void)
{
	struct film * head = NULL;  // 指向第一个结构的指针
	struct film * prev, * current;  // prev指向上一个结构的指针, current指向操作结构的指针
	char input[TSIZE];

	// 收集并存储信息
	puts("Enter first movie title: ");
	while (gets(input) && input[0] != '\0')  // 如果不需要就不要用malloc创建一个新的动态结构, 所以先创建一个变量input
	{
		current = (struct film *)malloc(sizeof(struct film));
		if (NULL == head)
			head = current;
		else
			prev->next = current;
		current->next = NULL;
		strcpy(current->title, input);
		puts("Your rating<0-10>:");
		scanf("%d", &current->rating);
		while (getchar() != '\n')
			continue;
		puts("Enter next movie title(empty line to stop):");
		prev = current;
	}

	if (NULL == head)
		puts("No data entered.");
	else
		puts("Here is the movie list: ");
	current = head;  // 这里不直接用head遍历linked list是为了防止head的值被改变
	while (NULL != current)
	{
		printf("Movie: %s Rating: %d\n", current->title, current->rating);
		current = current->next;
	}

	current = head;
	while(current != NULL)
	{
		struct film * temp;
		temp = current->next;
		free(current);
		current = temp;
	}

	puts("Bye!");

	return 0;
}