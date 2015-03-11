// 程序清单 17.11
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "p521二叉树ADT.h"

// 局部数据类型定义
typedef struct pair
{
	Node * parent;
	Node * child;
}Pair;

// 局部函数原型
static Node * MakeNode(const Item * pi);  // 操作: 创建一个节点  操作前: 已经判断过该Item能够加入到树中, 树还没有满  操作后: 如果成功分配了一个节点, 则返回节点的地址, 否则返回NULL
static bool ToLeft(const Item * i1, const Item * i2);  // 操作: 判断i1是在i2的左支还是右支, 如果在左支返回true, 否则返回false
static bool ToRight(const Item * i1, const Item * i2);
static void AddNode(Node * new_node, Node * root);  // 操作: 把一个节点加入到树中
static void InOrder(const Node * root, void (*pfun)(Item item));
static Pair SeekItem(const Item * pi, const Tree * ptree);  // 1. parent == NULL && child == NULL 没有根节点   2. parent == p父 && child == p父->left / p父->right == NULl 找到了位置, 直接用新地址替换NULL   3. parent == p父 && child == p父->left / p父->right != NULL 找到了同名同类的, child指向的非NULL就是
static void DeleteNode(Node ** ptr);
static void DeleteAllNodes(Node * ptr);

void InitializeTree(Tree * ptree)
{
	ptree->root = NULL;
	ptree->size = 0;
}

bool TreeIsEmpty(const Tree * ptree)
{
	return ptree->root == NULL && ptree->size == 0;
}

bool TreeIsFull(const Tree * ptree)
{
	return ptree->size == MAXITEMS;
}

int TreeItemCount(const Tree * ptree)
{
	return ptree->size;
}

bool AddItem(const Item * pi, Tree * ptree)
{
	Node * new_node;

	if (TreeIsFull(ptree))
	{
		fprintf(stderr, "Tree is full\n");
		return false;  // 提前返回
	}
	// 判断新的Item是否能够加入到树中
	if (SeekItem(pi, ptree).child != NULL)  // 如果定位的项目没有空next连接 (此时返回child的实际是名字和类型相同的节点的地址)
	{
		fprintf(stderr, "Attempted(未遂的,\
			企图的) to add duplicate(v.复制,\
			使加倍 n.副本, 复制品) item\n");
		return false;
	}
	// 为新的Item分配节点
	new_node = MakeNode(pi);  // 指向新节点
	if (new_node == NULL)  // 如果没能成功分配内存
	{
		fprintf(stderr, "Could't creat node.\n");
		return false;
	}
	// 成功创建了一个新节点
	ptree->size++;
	// 开始把节点加进树中
	if (ptree->root == NULL)  // 情况1: 树为空树
		ptree->root = new_node;  // 新节点即为树的根节点
	else                    // 情况2: 树非空
		AddNode(new_node, ptree->root);  // 为新节点寻找合适的位置, 并加进去
	return true;  // 成功返回
}

bool IsIntree(const Item * pi, const Tree * ptree)
{
	return (SeekItem(pi, ptree).child == NULL) ? false : true;
}

bool DeleteItem(const Item * pi, Tree * ptree)
{
	Pair look;
	look = SeekItem(pi, ptree);
	if (look.child == NULL)  // 没有找到要删除的项目
		return false;
	if (look.parent == NULL)  // 删除根项目
		DeleteNode(&ptree->root);  // 如果ptree->root == NULL 则没有根项目删除, 否则删除根项目   ???
	else if (look.parent->left == look.child)
		DeleteNode(&look.parent->left);
	else
		DeleteNode(&look.parent->right);
	ptree->size--;

	return true;
}

void Traverse(const Tree * ptree, void (*pfun)(Item item))
{
	if (ptree != NULL)
		InOrder(ptree->root, pfun);
}

void DeleteAll(Tree * ptree)
{
	if (ptree != NULL)
		DeleteAllNodes(ptree->root);
	ptree->root = NULL;
	ptree->size = 0;
}

static Pair SeekItem(const Item * pi, const Tree * ptree)  // *pi用于和项目比较以确定那个往左走还是往右走
{
	Pair look;
	look.parent = NULL;
	look.child = ptree->root;

	if (look.child == NULL)
		return look;  // 提前返回
	while (look.child != NULL)
	{
		if (ToLeft(pi, &(look.child->item)))  // 如果应该往左走
		{
			look.parent = look.child;
			look.child = look.child->left;
		}
		else if (ToRight(pi, &(look.child->item)))  // 如果是往右走
		{
			look.parent = look.child;
			look.child = look.child->right;
		}
		else  // 如果前面两种情况都不满足的话, 必定是相等的情况
			break;  // 如果相等了, look.child是目标节点的地址
		// 这里还隐藏这一种情况 parent == NULL child != NULL 根节点与目标相同
	}
	return look;  // 成功返回
}

static bool ToLeft(const Item * i1, const Item * i2)
{
	int comp1;

	if ((comp1 = strcmp(i1->petname, i2->petname)) < 0)  // 如果目标项目的名字比所在项目Ascii小
		return true;
	else if (comp1 == 0 && strcmp(i1->petkind, i2->petkind) < 0)  // 如果名字相同就比较种类
		return true;
	else
		return false;
}

static bool ToRight(const Item * i1, const Item * i2)
{
	int comp1;

	if ((comp1 = strcmp(i1->petname, i2->petname)) > 0)
		return true;
	else if (comp1 == 0 && strcmp(i1->petkind, i2->petkind) > 0)
		return true;
	else
		return false;
}

static Node * MakeNode(const Item * pi)
{
	Node * new_node;

	new_node = (Node *)malloc(sizeof(Node));
	if (new_node != NULL)  // 如果成功分配了内存
	{
		new_node->item = *pi;
		new_node->left = NULL;
		new_node->right = NULL;
	}
	return new_node;  // 即使没能够成功分配返回了NULL也返回去, 让调用函数做判断然后报错
}

static void AddNode(Node * new_node, Node * root)
{
	if (ToLeft(&new_node->item, &root->item))
	{
		if (root->left == NULL)  // 空子树
			root->left = new_node;  // 因此把节点添加到此处
		else
			AddNode(new_node, root->left);  // 否则递归处理该子树
	}
	else if (ToRight(&new_node->item, &root->item))
	{
		if (root->right == NULL)
			root->right = new_node;
		else
			AddNode(new_node, root->right);
	}
	else  // 不应该含有相同的项目
	{
		fprintf(stderr, "location error in AddNode()\n");
		exit(1);
	}
}

static void DeleteNode(Node ** ptr)  // ptr是指向目标节点的父节点指针成员地址
{
	Node * temp;
	puts((*ptr)->item.petname);
	if ((*ptr)->left == NULL)
	{
		temp = *ptr;
		*ptr = (*ptr)->right;
		free(temp);
	}
	else if ((*ptr)->right == NULL)
	{
		temp = *ptr;
		*ptr = (*ptr)->left;
		free(temp);
	}
	else  // 被删除节点有两个子节点
	{
		for (temp = (*ptr)->left; temp->right != NULL;
			temp = temp->right)
			continue;
		temp->right = (*ptr)->right;
		temp = *ptr;
		*ptr = (*ptr)->left;
		free(temp);
	}
}

static void InOrder(const Node * root, void (*pfun)(Item item))
{
	if (root != NULL)
	{
		InOrder(root->left, pfun);
		(*pfun)(root->item);
		InOrder(root->right, pfun);
	}
}

static void DeleteAllNodes(Node * root)
{
	Node * pright;

	if (root != NULL)
	{
		pright = root->right;
		DeleteAllNodes(root->left);
		free(root);
		DeleteAllNodes(pright);
	}
}