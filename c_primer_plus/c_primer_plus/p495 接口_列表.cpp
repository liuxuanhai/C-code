// 程序清单 17.3
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