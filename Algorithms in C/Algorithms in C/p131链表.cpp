//	1. 双向链表 doubly linked list 单链接 singly linked	头 head	尾 tail	circular list循环链表
//	2. 哨兵:
//		1. 帮助忽视表头和表尾的边界条件, 这样的调整将一个常规的双向链表转变成了一个有哨兵的双向循环链表;
//		2. 使用哨兵的好处是使得代码简洁而不是提高速度;
//		3. 做好使用哨兵空间成本与代码简洁收益之间的平衡;
typedef struct node * link;
struct node
{
	int		key;	// 关键字key
	link	prev;
	link	next;
};

//#define 无哨兵

#ifdef 无哨兵
struct list
{
	link head;
};
#else
struct list
{
	node nil;
};
#endif

#ifdef 无哨兵
link ListSearch(list & L, int k)
{
	link x = L.head;
	while (x != nullptr && x->key != k)
		x = x->next;
	return x;
}
#else
link ListSearch(list & L, int k)
{
	link x = L.nil.next;
	while (x != &L.nil && x->key != k)
		x = x->next;
	return x;
}
#endif

#ifdef 无哨兵
// 插入到链表的前端
void ListInseart(list & L, link x)
{
	x->prev = nullptr;
	x->next = L.head;
	if (nullptr != L.head)
		L.head->prev = x;
	L.head = x;
}
#else
void ListInseart(list & L, link x)
{
	x->prev = &L.nil;
	x->next = L.nil.next;
	L.nil.next->prev = x;
	L.nil.next = x;
}
#endif

#ifdef 无哨兵
// 链表的删除
void ListDelete(list & L, link x)
{
	if (nullptr != x->prev)
		x->prev->next = x->next;
	else
		L.head = x->next;
	if (nullptr != x->next)
		x->next->prev = x->prev;
}
#else
void ListDelete(list & L, link x)
{
	x->prev->next = x->next;
	x->next->prev = x->prev;
}
#endif