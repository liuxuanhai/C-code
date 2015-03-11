#include <iostream>
using namespace std;
#include "05dxList.h"
void show(List::link li)
{
	cout << li->item << endl;
}
int main(void)
{
	List lis;
	lis.AddNext(lis.GetSentinel(), 1);
	lis.AddTail(2);
	lis.AddTail(3);
	lis.AddHead(0);

	lis.DelHead();
	List::link li;
	lis.RemoveNext(lis.GetHead(), li);
	lis.AddTail(li);
	lis.RemoveHead(li);
	lis.AddTail(li);
	lis.RemoveTail(li);
	lis.AddNext(lis.Search(2), li);
	lis.SetItem(lis.Search(1)->next, 4);

	lis.Travel(show);
}