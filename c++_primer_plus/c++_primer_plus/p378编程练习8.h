// 编程练习 10.10 (8) 头文件
#ifndef AAA
#define AAA
typedef int Item;  // Item 项目
class List
{
private:
	enum{LEN = 5};
	Item list[LEN];
	int top;
public:
	List();
	void show() const;
	bool add(Item);
	bool isempty() const;
	bool isfull() const;
	void visit(void (*pf)(Item &));  // pf指向一个将Item引用作为参数的函数(不是成员函数)
		// visit将该函数用于列表中的每个数据项
};
#endif