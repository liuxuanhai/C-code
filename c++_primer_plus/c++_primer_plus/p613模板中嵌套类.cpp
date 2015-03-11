#ifndef 程序清单_15_5
#define 程序清单_15_5

template <class Item>
class QueueTP
{
private:
	enum{Q_SIZE = 10};  // 默认队列的长度
	// Node 是一个嵌套的类定义
	class Node
	{
	public:
		Item item;
		Node * next;
		Node(const Item & i) : item(i), next(nullptr){} 
	};
	Node * front;        // 头指针
	Node * rear;         // 尾指针
	int items;           // 现在的项目数目
	const int qsize;     // 最大的项目个数   ??? 难道const常数也可以这样进行声明然后初始化的时候给定值 ???
	QueueTP(const QueueTP & q) : qsize(0) {}
	QueueTP & operator=(const QueueTP & q) {return *this;}
public:
	QueueTP(int qs = Q_SIZE);
	~QueueTP();
	bool isempty() const {return items == 0;}
	bool isfull() const {return items == qsize;}
	int queuecount() const {return items;}
	bool enqueue(const Item & item);  // 加项目
	bool dequeue(Item & item);        // 减项目
};

template <class Item>
QueueTP<Item>::QueueTP(int qs) : qsize(qs)
{
	front = rear = nullptr;
	items = 0;
}

template<class Item>
QueueTP<Item>::~QueueTP()
{  // 这里只需要销毁堆中的内存就行了, 栈中的自动销毁
	Node * temp;
	while (front != nullptr)  // 如果不是空队列
	{
		temp = front;
		front = front->next;
		delete temp;
	}
}

template<class Item>
bool QueueTP<Item>::enqueue(const Item & item)
{
	if (isfull())
		return false;
	Node * add = new Node(item);  // 创建node, 并调用构造函数进行初始化
	items++;
	if (front == nullptr)
		front = add;
	else
		rear->next = add;
	rear = add;
	return true;
}

template<class Item>
bool QueueTP<Item>::dequeue(Item & item)
{
	if (front == nullptr)
		return false;
	item = front->item;
	items--;
	Node * temp = front;
	front = front->next;
	delete temp;
	if (items == 0)
		return rear = nullptr;
	return true;
}

#endif

// 程序清单 15.6
#include <iostream>
#include <string>

int main(void)
{
	using std::string;
	using std::cin;
	using std::cout;

	QueueTP<string> cs(5);  // 创建一个五个元素的队列
	string temp;

	while (!cs.isfull())
	{
		cout << "Please enter your name, you will be served in the order of arrival.\n name: ";
		getline(cin, temp);
		cs.enqueue(temp);
	}
	cout << "The queue is full, Processing begins!\n";
	while (!cs.isempty())
	{
		cs.dequeue(temp);
		cout << "Now processing " << temp << "...\n";
	}

	return 0;
}