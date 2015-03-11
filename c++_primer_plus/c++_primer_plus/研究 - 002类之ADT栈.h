// p373开始 p377结束

// 类之ADT(abstract data type, 抽象数据类型)

#ifndef 栈_H_
#define 栈_H_

typedef unsigned long Item;	// 这里使用的是Item来代替unsigned long, 如果需要duoble栈或结构类型的栈, 则只需修改typedef语句, 类声明和方法定义保持不变;

class Stack
{
private:
	enum {MAX = 10};
	Item items[MAX];
	int	 top;	// top 指向栈顶的空位置
public:
	Stack();
	bool isEmpty() const;
	bool isFull()  const;
	bool push(const Item & item);
	bool pop(Item & item);
};

#endif