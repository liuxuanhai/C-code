#ifndef LIST_H_
#define LIST_H_

// #### 特定于本程序的声明 #####
#define TSIZE 45
struct film
{
	char title[TSIZE];
	int rating;
};
typedef struct film Item;

// ##### 一般类型声明 #####
typedef struct node
{
	Item item;
	struct node * next;
}Node;

typedef Node * List;

void InitializeList(List * plist);

bool ListIsEmpty(const List * plist);

bool ListIsFull(const List * plist);

unsigned int ListItemCount(const List * plist);

bool AddItem(Item item, List * plist);

void Traverse(const List * plist, void(* pfun)(Item item));

void EmptyTheList(List * plist);

#endif

// 程序清单 17.5
#include <stdio.h>
#include <stdlib.h>

static void CopyToNode(Item item, Node * pnode);

void InitializeList(List * plist)
{
	*plist = NULL;
}

bool ListIsEmpty(const List * plist)
{
	return *plist == NULL ? true : false;
}

bool ListIsFull(const List * plist)
{
	bool full;
	Node * temp;
	if ((temp = (Node *)malloc(sizeof(Node))) == NULL)
		full = true;
	else
		full = false;
	free(temp);
	return full;
}

unsigned int ListItemCount(const List * plist)
{
	Node * current = *plist;
	unsigned int ct = 0;
	while (current != NULL)
	{
		ct++;
		current = current->next;
	}
	return ct;
}

bool AddItem(Item item, List * plist)
{
	Node * temp, * current;
	current = (Node *)malloc(sizeof(Node));
	if (current == NULL)
		return false;
	current->next = NULL;
	CopyToNode(item, current);
	if (*plist == NULL)
		*plist = current;
	else
	{
		temp = *plist;
		while (temp->next != NULL)
			temp = temp->next;  // temp++ 是个可笑的错误呀
		temp->next = current;
	}
	return true;
}

void Traverse0(const Node * pnode, void (*pfun)(Item item))
{
	if (pnode != NULL)
	{
		Traverse0(pnode->next, pfun);
		pfun(pnode->item);
	}
}

void Traverse(const List * plist, void (*pfun)(Item item))
{
	Node * temp = *plist;
	if (*plist != NULL)
		Traverse0(*plist, pfun);
}

void EmptyTheList(List * plist)
{
	Node * temp = *plist;
	*plist = NULL;
	Node * temp2;
	while (temp != NULL)
	{
		temp2 = temp->next;
		free(temp);
		temp = temp2;
	}
}

static void CopyToNode(Item item, Node * pnode)
{
	pnode->item = item;
}

// 程序清单 17.4
#include <stdio.h>
#include <stdlib.h>

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