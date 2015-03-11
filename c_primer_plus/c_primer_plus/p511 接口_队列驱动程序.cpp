// 程序清单 17.8
#include <stdio.h>
#include "p504 接口_队列.h"

int main(void)
{
	Queue line;
	Item temp;
	char ch;

	InitializeQueue(&line);
	puts("a> add   d> delete   q> quit");
	while ('q' != (ch = getchar()))
	{
		if (ch != 'a' && ch != 'd')
			continue;
		if (ch == 'a')
		{
			printf("Integer to add: ");
			scanf("%d", &temp);
			if (!QueueIsFull(&line))
			{
				printf("Puttine %d into queue\n", temp);
				EnQueue(temp, &line);
			}
			else
				puts("Queue is full!");
		}
		else
		{
			if (QueueIsEmpty(&line))
				puts("Nothing to delete!");
			else
			{
				DeQueue(&temp, &line);
				printf("Removing %d from queue\n", temp);
			}
		}
		printf("%d items in queue\n", QueueItemCount(&line));
		puts("Type a to add, d to delete, q to quit: ");
	}
	EmptyTheQueue(&line);
	puts("Bye!");

	return 0;
}