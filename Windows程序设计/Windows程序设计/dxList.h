#include <windows.h>
class List
{
public:
	typedef RECT	Item;
	typedef struct	node
	{
		Item	item;
		node    * next;
	} * link;
	
private:
	node nilNode;	// 哨兵节点
	link linkTail;	// 指向尾节点 初始化指向的是哨兵节点
	void ItemIni	(Item & item){ SetRect(&item, 0, 0, 0, 0); }				// 特定类型 初始化
	void ItemAssign	(Item & L, Item & R){ L = R; }			// 特定类型 赋值
public:
	BOOL ItemIsEqual(Item & L, Item & R) { const int SNAKEWIDTH = L.right - L.left; POINT ptTemp = {R.left + SNAKEWIDTH / 2, R.top + SNAKEWIDTH / 2}; return ((PtInRect(&L, ptTemp))); }	// 特定类型 判断是否相等
	int  length;

	List();
	~List();

			// 查

	// 遍历链表, 并能将一个函数作用于每个节点
	void Travel(void (*fun)(link));

	// 遍历链表, 并将指定项目的节点的前一个节点找出
	link Search(Item, link beg = NULL);

	// 获取哨兵/表头/表尾节点的链接
	link GetSentinel()	{ return &nilNode; }
	link GetHead()		{ return nilNode.next; }
	link GetTail()		{ return linkTail; }

			// 增

	// 给表的任意指定位置增加节点
	void AddNext(link, link);
	void AddNext(link, Item);

	// 给表头增加节点
	void AddHead(link);
	void AddHead(Item);

	// 给表尾增加节点
	void AddTail(link);
	void AddTail(Item);

			// 删

	// 移除/删除表中指定链接后边的节点
	bool RemoveNext(link, link &);
	bool DelNext(link);

	// 移除/删除表中第一个指定item节点
	bool RemoveItem(Item, link &);
	bool DelItem(Item);

	// 移除/删除表中头节点
	bool RemoveHead(link &);
	bool DelHead();

	// 移除/删除表中尾节点
	bool RemoveTail(link &);
	bool DelTail();

			// 改

	// 更改指定节点里面的Item
	void SetItem(link, Item);
};