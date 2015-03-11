// 程序清单 17.4
#include <stdio.h>
#include <stdlib.h>      // 为exit()提供原型
#include "p495接口_列表.h"    // 定义list, item
#include "daxiong.h"

void showmovies (Item item);

int main (void)
{
	List movies;
	Item temp;

	// 初始化 (把列表设置为NULL)
	InitializeList (&movies);
	if (ListIsFull (&movies))  // 即判断内存是否已满, 能不能为其分配空间
	{
		fprintf (stderr, "No memory available! Bye!\n");
		exit (1);
	}

	// 收集并存储
	puts ("Enter first movie title: ");
	while (gets (temp.title) != NULL && temp.title[0] != '\0')
	{
		puts ("Enter your rating <0-10>: ");
		scanf ("%d", &temp.rating);
		eatline ();
		if (AddItem (temp, &movies) == false)
		{
			fprintf (stderr, "Problem allocating memory\n");
			break;
		}
		puts ("Enter next movie title (empty line to stop): ");
	}

	// 显示
	if (ListIsEmpty (&movies))
		printf ("No data entered. ");
	else
	{
		printf ("Here is the movie list: \n");
		Traverse (&movies, showmovies);
	}
	printf ("You entered %d movies.\n", ListItemCount (&movies));

	// 清除
	EmptyTheList (&movies);
	printf ("Bye!\n");

	return 0;
}

void showmovies (Item item)
{
	printf ("Movie: %s Rating: %d\n", item.title,
		item.rating);
}