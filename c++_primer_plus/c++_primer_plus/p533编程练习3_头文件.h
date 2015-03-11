// 动态内存分配可能需要重新定义的函数: 析构函数, 复制函数, =运算符
#ifndef 动态内存_友元_13_7_3
#define 动态内存_友元_13_7_3
#include <iostream>

class ABC
{
private:
	char * label;
	int rating;
public:
	ABC(const char * l = "NoLabel", int ra = -1);  // 默认构造函数
	ABC(const ABC & abc);  // 复制构造函数
	virtual ~ABC() = 0;  // 虚析构函数  // 实在没有什么让派生类必须重写的, 所以这里变成纯虚函数, 仅仅是为了不让他生成对象
	virtual ABC & operator*()  { return *this; }
	ABC & operator=(const ABC & abc);  // 赋值函数  
	virtual void View() const;
	friend std::ostream & operator<<(std::ostream & os, const ABC &);  // 如果加上virtual和=0会怎么样啊   error C2254: “<<”: 友元函数上不允许使用纯说明符或抽象重写说明符
	// 派生类一样可以用这个
};

class baseDMA : public ABC
{
public:
	//baseDMA(const char * l = "null", int r = 0); // 自动生成默认构造函数, 默认构造函数自动调用基类的默认构造函数
	//baseDMA(const baseDMA & rs);  // 复制函数  // 也是自动调用基类的复制构造函数
	//~baseDMA();  //这里的析构函数会自动生成, 而且基类定义了虚的, 这里的也会生成虚的
	//baseDMA & operator=(const baseDMA & rs);  // 自动生成的赋值函数会调用基类的赋值函数
	baseDMA(const char * l = "NoLabel", int r = 0);
};

// 一个继承了使用动态内存分配基类而自身没有使用动态内存分配的派生类
class lacksDMA : public ABC
{
private:
	enum {COL_LEN = 40};
	char color[COL_LEN];  // 没有使用动态内存分配的一个指针的(char *)方式保存字符串而是选择了字符数组的形式
public:
	lacksDMA(const char * c = "blank", const char * l = "null", int r = 0);
	lacksDMA(const char * c, const ABC & rs);
	void View() const;
	//friend std::ostream & operator<<(std::ostream & os, const lacksDMA & rs);  // 友元输出函数
};

// 基类使用了动态内存分配, 派生类也使用了的情况
class hasDMA : public ABC
{
private:
	char * style;  // 在构造函数为其使用动态内存分配
public:
	hasDMA(const char * s = "none", const char * l = "null", int r = 0);
	hasDMA(const char * s, const ABC & rs);
	hasDMA(const hasDMA & hs);  // 复制构造函数
	virtual ~hasDMA();
	virtual hasDMA & operator=(const hasDMA & rs);  // 赋值函数
	void View() const;
	//friend std::ostream & operator<<(std::ostream & os, const hasDMA & rs);
};

#endif