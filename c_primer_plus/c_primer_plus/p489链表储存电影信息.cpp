// 程序清单 17.2
#include <stdio.h>
#include <stdlib.h>  // 提供malloc()原型
#include <string.h>  // 提供strcpy()原型
#define TSIZE 45     // 片名长度限制
struct film {
	char title[TSIZE];
	int rating;
	struct film * next;
};

int main (void)
{
	struct film * head = NULL;
	struct film * prev, * current;
	char input[TSIZE];

	// 收集并存储信息
	puts ("Enter first movie title: ");
	while (gets (input) != NULL && input[0] != '\0')
	{
		current = (struct film *) malloc (sizeof (struct film)); //如果malloc的返回值为null表示他无法获取所需内存
		if (NULL == head)
			head = current;
		else
			prev->next = current;
		current->next = NULL;
		strcpy (current->title, input);
		puts ("Enter your rating <0 - 10>: ");
		scanf ("%d", &current->rating);
		while (getchar () != '\n')
			continue;
		puts ("Enter next movie title (empty line to stop): ");
		prev = current;
	}

	// 给出电影列表
	if (NULL == head)
		puts ("No data entered. ");
	else
		puts ("Here is the movie list: ");
	current = head;
	while (NULL != current)
	{
		printf ("Movie: %s Rating: %d\n", current->title, current->rating);
		current = current->next;
	}

	// 任务完成, 释放分配的内存
	current = head;
	while (current != NULL)
	{
		struct film * temp;
		temp = current ->next; // 书上这里写错了!
		free (current);
		current = temp;
	}
	puts ("Bye!");

	return 0;
}