// 程序清单 17.10
#ifndef _ercharshu_h_
#define _ercharshu_h_
#define MAXITEM 10  // 二叉树容纳的最多项目个数
typedef struct item
{
	char petname[20];
	char petkind[20];
}Item;
typedef struct node
{
	Item item;
	struct node * left;
	struct node * right;
}Node;
typedef struct tree
{
	Node * root;
	int ct;
}Tree;

void Ini(Tree * ptree);
int TreeItemCount(const Tree * ptree);
bool TreeIsFull(const Tree * ptree);
bool TreeIsEmpty(const Tree * ptree);
bool AddItem(Tree * ptree, const Item * pitem);  // const说明的是ptree指向的Tree里面的内容根节点不能改, 但是添加的时候也包括添加根节点, 所以添加的时候const还是不能加上
bool DeleteItem(Tree * ptree, const Item * pitem);
bool IsInTree(const Tree * ptree, const Item * pitem);
void Traverse(const Tree * ptree, void (*fun)(Item item));
void DeleteAll(Tree * ptree);

#endif