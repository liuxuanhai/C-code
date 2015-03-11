// 程序清单 17.4
#include <stdio.h>
#include <stdlib.h>
#include "p495 接口_列表.cpp"

void showMovies(Item item);

int main(void)
{
	List Movies;
	Item temp;

	InitializeList(&Movies);
	if (ListIsFull(&Movies))
	{
		printf("No memory available! Bye!\n");
		exit(1);
	}

	puts("Enter first movie title: ");
	while (gets(temp.title) && temp.title[0])
	{
		puts("Rating: ");
		scanf("%d", &temp.rating);
		while (getchar() != '\n');
		if (AddItem(temp, &Movies) == false)
		{
			fprintf(stderr, "Problem allocating memory\n");
			break;
		}
		puts("Enter next movie title (empty line to stop): ");
	}

	if (ListIsEmpty(&Movies))
		printf("No data entered.\n");
	else
	{
		printf("Here is the movie list: \n");
		Traverse(&Movies, showMovies);
	}
	printf("You enteren %d movies.\n", ListItemCount(&Movies));

	EmptyTheList(&Movies);
	printf("Bye.\n");

	return 0;
}

void showMovies(Item item)
{
	printf("Movie: %s Rating: %d\n", item.title, item.rating);
}