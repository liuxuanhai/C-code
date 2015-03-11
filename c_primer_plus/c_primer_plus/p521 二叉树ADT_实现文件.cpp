// 程序清单 17.11
#include <stdio.h>
#include <stdlib.h>  // malloc() free()
#include <string.h>  // strcmp()
#include "p521 二叉树ADT.h"

typedef struct three
{
	Node * parent;
	Node * child;
	Node ** add;
}Three;

static Node * MakeNode(const Item * pitem);
static Th
	ree SeekItem(const Tree * ptree, const Item * pitem);
static int LeftOrRight(const Node * pnode, const Item * pitem);
static void DeleteNode(Node ** ppnode);
static void InOrder(const Node * root, void (*pfun)(Item item));
static void DeleteAllNodes(Node * pnode);

void Ini(Tree * ptree)
{
	ptree->ct = 0;
	ptree->root = NULL;
}

int TreeItemCount(const Tree * ptree)  // 这里传递的是Tree的地址ptree, 他是一个值, 所以在这里即使把ptree改变了也会在函数退出时对原来的地址没有任何影响
{
	return ptree->ct;
}

bool TreeIsEmpty(const Tree * ptree)
{
	return ptree->ct == 0;
}

bool TreeIsFull(const Tree * ptree)
{
	return ptree->ct == MAXITEM;
}

bool AddItem(Tree * ptree, const Item * pitem)
{
	if (TreeIsFull(ptree))
		return false;
	Node * temp;
	if ((temp = MakeNode(pitem)) == NULL)
	{
		fprintf(stderr, "无法为新节点分配内存!\n");
		return false;
	}
	Three three;
	three = SeekItem(ptree, pitem);
	if (three.child != NULL)
	{
		fprintf(stderr, "已经有了相同的项目了\n");
		free(temp);
		return false;
	}
	*three.add = temp;  // 即使是空树也能加上去
	ptree->ct++;
	return true;
}

bool DeleteItem(Tree * ptree, const Item * pitem)
{
	Three look;
	look = SeekItem(ptree, pitem);
	if (look.child == NULL)  // 没有找到待删除项目
		return false;
	if (look.parent == NULL)  // 没有根项目或者根项目就是待删除项目
		DeleteNode(&ptree->root);
	else if (look.parent->left == look.child)  // 如果是左边
		DeleteNode(&look.parent->left);
	else
		DeleteNode(&look.parent->right);
	ptree->ct--;
	return true;
}

bool IsInTree(const Tree * ptree, const Item * pitem)
{
	return SeekItem(ptree, pitem).child != NULL;
}

void Traverse(const Tree * ptree, void (*pfun)(Item item))
{
	if (ptree == NULL)
		return;
	if (ptree->root != NULL)
	{
		InOrder(ptree->root, pfun);  // 由于是两个分支都要涉及到而不是像seekItem中只涉及一个分支, 所以用递归实现方便
			// 由于ptree用的是root, 而其他的是用的left和right, 所以要重新分一个函数避开名字上的不一致
	}
}

void DeleteAll(Tree * ptree)
{
	if (ptree->root != NULL)
		DeleteAllNodes(ptree->root);
	ptree->root = NULL;
	ptree->ct = 0;
}

static Node * MakeNode(const Item * pitem)
{
	Node * temp;
	temp = (Node *)malloc(sizeof(Node));
	if (temp != NULL)
	{
		temp->item = *pitem;
		temp->left = NULL;
		temp->right = NULL;
	}
	return temp;
}

//==============================================================
// 1. parent == NULL child == NULL (add != NULL) 此时没有根节点
// 2. parent == NULL chile != NULL (add != NULL) 此时有根节点 并且根节点就是与目标项相同的
// 3. parent != NULL child == NULL (add != NULL) 此时找到了添加的位置, add指向他就行
// 4. (parent != NULL) child != NULL (add != NULL) 此时有了相同的项目, child指向相同项目
static Three SeekItem(const Tree * ptree, const Item * pitem)
{
	Three temp;
	temp.parent = NULL;
	temp.child = ptree->root;
	temp.add = (Node **)&ptree->root;  // 这里是一个消除const的方法!!!!!!!!
	if (ptree->root == NULL)
		return temp;
	while (temp.child != NULL)
	{
		switch(LeftOrRight(temp.child, pitem))
		{
		case 1:   // ######### 这里是数字1 而不是字符'1' ##########
			temp.add = &temp.child->left;
			temp.parent = temp.child;
			temp.child = temp.child->left;
			break;
		case -1: 
			temp.add = &temp.child->right;
			temp.parent = temp.child;
			temp.child = temp.child->right;
			break;
		case 0:
			return temp;  // 这种情况又无法表示项目相同了!!!!!!!!!!!!!!!!
			// 第一次循环就是case '0' 的话就有有情况2
		}
	}
	return temp;
}

static int LeftOrRight(const Node * pnode, const Item * pitem)
{
	int cpy, cpy1;
	if ((cpy = strcmp(pnode->item.petname, pitem->petname)) > 0)
		return -1;
	if (cpy == 0 && ((cpy1 = strcmp(pnode->item.petkind, pitem->petkind)) > 0))
		return -1;
	if ((cpy == 0 && cpy1 < 0) || (cpy < 0))
		return 1;
	if (cpy == 0 && cpy1 == 0)
		return 0;
}

static void DeleteNode(Node ** ppnode)
{
	Node * temp;
	puts((*ppnode)->item.petname);
	if ((*ppnode)->left == NULL)  // 待删项目左支为空
	{
		temp = *ppnode;
		*ppnode = (*ppnode)->right;
		free(temp);
	}
	else if ((*ppnode)->right == NULL)  // 待删项目右支为空
	{
		temp = *ppnode;
		*ppnode = (*ppnode)->left;
		free(temp);
	}
	else  // 待删项目左右支都不为空
	{
		for (temp = (*ppnode)->left; temp->right != NULL;
			temp = temp->right)
			continue;
		temp->right = (*ppnode)->right;
		temp = *ppnode;
		*ppnode = (*ppnode)->left;
		free(temp);
	}
}

static void InOrder(const Node * pnode, void (*pfun)(Item item))
{
	if (pnode != NULL)
	{
		InOrder(pnode->left, pfun);
		(*pfun)(pnode->item);
		InOrder(pnode->right, pfun);
	}
}

static void DeleteAllNodes(Node * pnode)
{
	Node * temp;
	if (pnode != NULL)
	{
		temp = pnode->right;
		DeleteAllNodes(pnode->left);
		free(pnode);
		DeleteAllNodes(temp);
	}
}