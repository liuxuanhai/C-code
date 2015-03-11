// 编程练习 17.12
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "p539编程练习7(二叉树).h"

typedef struct
{
	Node * parent;
	Node * child;
	Node ** add;
}Three;
enum LorR{left, right, same};

static Node * MakeNode(const Item *);
static Three SeekItem(const Tree *, const Item *);
static LorR LeftOrRight(const Node *, const Item *);
static void DeleteNode(Node **);
static void InOrder(const Node *, void (*pfun)(Node *));

void Ini(Tree * pt)
{
	pt->root = NULL;
	pt->size = 0;
}

bool AddItem(const Item * pi, Tree * pt)
{
	Node * temp;
	Three three;
	if (TreeIsFull(pt))  // 如果树满了, 加入失败
		return false;
	if ((temp = MakeNode(pi)) == NULL)  // 分配动态内存失败
	{
		fprintf(stderr, "无法给Node分配动态内存!\n");
		return false;
	}
	if ((three = SeekItem(pt, pi)).child != NULL)  // 找到了相同的项目
	{
		three.child->count++;
		free(temp);
		return true;
	}
	*three.add = temp;
	pt->size++;
	return true;
}

static Three SeekItem(const Tree * pt, const Item * pi)
{
	Three three;
	three.parent = NULL;
	three.child = pt->root;
	three.add = (Node **)&pt->root;

	if (pt->root == NULL)  // 如果是空树, 返回
		return three;
	while (three.child != NULL)
	{
		switch (LeftOrRight(three.child, pi))
		{
		case left :
			three.parent = three.child;
			three.add = &three.child->left;  // 注意 add一定在child改值之前
			three.child = three.child->left;
			break;
		case right :
			three.parent = three.child;
			three.add = &three.child->right;
			three.child = three.child->right;
			break;
		case same :
			return three; // 第一次执行while就same返回的是parent == NULL child != NULL;
		default :
			fprintf(stderr, "switch() error!\n");
		}
	}
	return three;
}

static LorR LeftOrRight(const Node * pn, const Item * pi)
{
	int temp;
	if ((temp = strcmp(pn->item.wrd, pi->wrd)) > 0)
		return left;
	else if (temp < 0)
		return right;
	else
		return same;

}

static Node * MakeNode(const Item * pi)
{
	Node * temp = (Node *)malloc(sizeof(Node));
	if (temp != NULL)
	{
		temp->item = *pi;
		temp->left = NULL;
		temp->right = NULL;
		temp->count = 1;
	}
	return temp;
}

bool DeleteItem(Item * pi, Tree * ptree)
{
	Three three;
	if (TreeIsEmpty(ptree))  // 如果是空的就不能删除了
		return false;
	if ((three = SeekItem(ptree, pi)).child == NULL)  // 如果没有找到相同项目
	{
		fprintf(stderr, "树中没有该项目\n");
		return false;
	}
	if (three.parent == NULL && three.child != NULL)  // 如果只有一个根项目
		DeleteNode(&ptree->root);
	else
		DeleteNode(three.add);
	ptree->size--;
	return true;
}

static void DeleteNode(Node ** ppn)
{
	Node * temp;
	if ((*ppn)->left == NULL)
	{
		temp = (*ppn);
		*ppn = (*ppn)->right;
		free(temp);
	}
	else if ((*ppn)->right == NULL)
	{
		temp = (*ppn);
		*ppn = (*ppn)->left;
		free(temp);
	}
	else
	{
		temp = (*ppn)->left;
		while (temp->right != NULL)
			temp = temp->right;
		temp->right = (*ppn)->right;
		temp = *ppn;
		*ppn = (*ppn)->left;
		free(temp);
	}
}

Node * IsInTree(const Item * pi, const Tree * ptree)
{
	return SeekItem(ptree, pi).child;
}

void Travel(const Tree * ptree, void (*pfun)(Node * pi))
{
	if (ptree != NULL)
		InOrder(ptree->root, pfun);
}

static void InOrder(const Node * pn, void (*pfun)(Node * pi))
{
	Node * temp;  // DeleteAll()的时候用的上
	if (pn != NULL)
	{
		InOrder(pn->left, pfun);
		temp = pn->right;
		pfun((Node *)pn);
		InOrder(temp, pfun);
	}
}

typedef void(*kkk)(Node * pn);  //========= 我草 ==========
void DeleteAll(Tree * pt)
{
	if (pt->root != NULL)
		Travel(pt, (kkk)free);
	pt->root = NULL;
	pt->size = 0;
}