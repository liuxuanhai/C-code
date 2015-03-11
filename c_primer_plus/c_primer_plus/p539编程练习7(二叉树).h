// 编程练习 17.12
#ifndef TREE_H
#define TREE_H
#define MAXITEMS 1000  // 树中保存的最大项目数目
#define SLEN 81  // 单词的最大长度
//=============================================
// 使用之前先typedef出Item
typedef struct item
{
	char wrd[SLEN];
}Item;
//=============================================

typedef struct node
{
	Item item;
	int count;  // 单词出现的次数
	struct node * left;
	struct node * right;
}Node;

typedef struct tree
{
	int size;  // 树中保存的项目个数
	Node * root;
}Tree;

void Ini(Tree * pt);
inline bool TreeIsFull(const Tree * pt){return pt->size == MAXITEMS;}
inline bool TreeIsEmpty(const Tree * pt){return pt->size == 0;}
inline int TreeItemCount(const Tree * pt){return pt->size;}
bool AddItem(const Item * pi, Tree * ptree);
bool DeleteItem(Item * pi, Tree * ptree);
Node * IsInTree(const Item * pi, const Tree * ptree);  // NULL 就是不在树里面
void Travel(const Tree * ptree, void (*pfun)(Node *));
void DeleteAll(Tree * ptree);

#endif