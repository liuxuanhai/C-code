// 编程练习 10.10 (5) 头文件
#ifndef _STACK_H_
#define _STACK_H_

struct customer {
	char fullname[35];
	double payment;
};
typedef struct customer Item;
class Stack
{
private:
	enum{SIZE = 5};
	Item stack[SIZE];
	double tot_payment;
	int num;
public:
	Stack();
	bool isempty() const {return num == 0;}
	bool isfull() const {return num >= SIZE;}
	bool add(const Item & stack_);
	bool de();
	void show() const;
};

#endif