#include "研究 - 006类之队列类.h"
#include <cstdlib>
Queue::Queue(int qs) : qsize(qs)
{
	front		= rear = NULL;
	itemsNum	= 0;
}

Queue::~Queue()
{
	link temp;
	while (front)
	{
		temp = front;
		front = front->next;
		delete temp;
	}
}

bool Queue::isEnQueue(const Item & item)
{
	if (isFull())
		return false;
	Node * add = new Node;
	add->item = item;
	add->next = NULL;
	itemsNum++;
	if (!front)
		front = add;
	else
		rear->next = add;
	rear = add;
	return true;
}

bool Queue::isDeQueue(Item & item)
{
	if (isEmpty())
		return false;
	itemsNum--;
	link CN = front;
	item = front->item;
	front = front->next;
	delete CN;
	if (itemsNum == 0)
		rear = NULL;
	return true;
}

void Customer::Set(long when)
{
	processtime = std::rand() % 3 + 1;
	arrive = when;
}