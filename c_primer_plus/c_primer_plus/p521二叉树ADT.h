// 程序清单 17.10
#ifndef _TREE_H_
#define _TREE_H_

typedef struct item
{
	char petname[20];
	char petkind[20];
}Item;

#define MAXITEMS 10  // 设计的二叉树最多容纳10个项目

typedef struct node
{
	Item item;
	struct node * left;   // 前项
	struct node * right;  // 后项
}Node;

typedef struct tree
{
	Node * root;  // 指向树根的指针
	int size;  // 树中项目的个数
}Tree;

// 操作: 把一个树初始化为空树
// 操作前: ptree指向一个树
// 操作后: 该树已被初始化为空树
void InitializeTree(Tree * ptree);

// 操作: 确定树是否为空
// 操作前: ptree指向一个树
// 操作后: 如果树为空则函数返回true; 否则返回false
bool TreeIsEmpty(const Tree * ptree);

// 操作: 确定树是否已满
// 操作前: ptree指向一个树
// 操作后: 如果树已满则返回true, 否则返回false
bool TreeIsFull(const Tree * ptree);

// 操作: 确定树中项目的个数
// 操作前: ptree指向一个树
// 操作后: 函数返回树中项目的个数
int TreeItemCount(const Tree * ptree);

// 操作: 向树中添加一个项目
// 操作前: pi是待添加项目的地址
//         ptree指向一个已经初始化的树
// 操作后: 如果可能, 函数把该项目添加到树中
//         返回true, 否则函数返回false
bool AddItem(const Item * pi, Tree * ptree);

// 操作: 在树中查找一个项目
// 操作前: pi指向一个项目
//		  ptree指向一个已经初始化的树
// 操作后: 如果该项目在树中, 则返回true, 否则返回false
bool IsIntree(const Item * pi, const Tree * ptree);

// 操作: 从树中删除一个项目
// 操作前: pi是待删除项目的地址
//         ptree指向一个已经初始化的树
// 操作后: 如果可能, 函数从树中删除该项目并返回true, 否则返回false
bool DeleteItem(const Item * pi, Tree * ptree);

// 操作: 把一个函数作用于书中的每一个项目
// 操作前: ptree指向一棵树
//         pfun指向一个没有返回值的函数, 该函数接受一个Item作为参数
// 操作后: pfun指向的函数被作用于树中的每个项目一次
void Traverse(const Tree * ptree, void (* pfun)(Item item));

// 操作: 从树中删除所有节点
// 操作前: ptree指向一个已经初始化的树
// 操作后: 该树为空树
void DeleteAll(Tree * ptree);

#endif