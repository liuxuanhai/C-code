#ifndef QUEUE_H_
#define QUEUE_H_

class Customer
{
private:
	long	arrive;
	int		processtime;
public:
	Customer(){arrive = processtime = 0;}

	void	Set(long when);
	long	GetWhen()	const {return arrive;}
	int		ptime()		const {return processtime;};
};

typedef Customer Item;

class Queue
{
private:
	typedef struct Node	{Item item; Node * next;} *link;	// 类中声明结构类型, private只能在类中使用, public要通过作用域解析符使用
	enum {Q_SIZE = 10};
	link	front;
	link	rear;
	int		itemsNum;
	const int qsize;	// 类声明一个常量, 在定义的时候必须初始化, 通过给构造函数使用初始化列表实现

		// 初始化列表详解:

	Queue(const Queue & q) : qsize(0){}
			// 调用Queue(const Queue & q)函数的时候: 1. 给对象的所有数据成员变量分配内存(这里是4个);	2. 程序进入到函数体中, 使用常规方式将值存储到内存中;
			// 因此, 在执行到构造函数体之前, 即创建对象时对常量qsize进行初始化; 实现这种特殊语法的名字叫成员初始化列表( : qsize(0));
			// 注意:
			//		1. 只有构造函数可以使用这种初始化列表语法;
			//		2. 必须使用这种语法的两种类成员:	(1). 非静态const类成员	(2). 被声明为引用的类成员(因为引用与const数据类似, 只能在被创建的时候进行初始化)
			//		3. 最好使用这种语法的情况:	对于本身就是类对象的成员来说, 使用成员初始化列表的效率更高;

		// 对错误的暂时用不到的默认生成的函数的处理

	Queue & operator=(const Queue & q){return *this;}

			// 在本例中, 默认的转换构造函数和赋值运算符是错误的, 但是这里暂时也用不着实现深度转换构造函数和深度复制赋值运算符, 所以这里将它们设置为private类型的函数, 以防止错误的使用;
			// 这样做有3个作用:
			//		1. 它避免了本来将自动生成的默认方法定义;
			//		2. 因为这些方法是私有的, 所以不能被广泛使用;
			//		3. 在定义其对象不允许被复制的类时, 这种方法很有用;
			//		ps: C++11提供了另一种禁用方法的方式 -- 使用关键字delete

public:
	Queue(int qs = Q_SIZE);
	~Queue();
	bool	isEmpty()	const	{return itemsNum == 0;};
	bool	isFull()	const	{return itemsNum == qsize;};
	int		iQueueCount()const	{return itemsNum;};
	bool	isEnQueue(const Item &item);
	bool	isDeQueue(Item & item);
};

#endif