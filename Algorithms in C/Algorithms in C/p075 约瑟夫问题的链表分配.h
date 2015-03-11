#ifndef LIANBIAO_H_
#define LIANBIAO_H_

typedef struct node *link;
typedef int			Item;
struct node
{
	Item item;
	link next;
};

void initNode(int n);
link newNode(Item);
void freeNode(link);
void insertNode(link, link);
link deleteNext(link);

#endif