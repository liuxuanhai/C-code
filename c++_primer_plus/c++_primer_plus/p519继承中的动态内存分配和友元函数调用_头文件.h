// 动态内存分配可能需要重新定义的函数: 析构函数, 复制函数, =运算符
#ifndef 动态内存_友元_13_7_3
#define 动态内存_友元_13_7_3
#include <iostream>

class baseDMA
{
private:  // label 标签
	char * label;  // 要使用构造函数为其动态分配内存
	int rating;
public:
	baseDMA(const char * l = "null", int r = 0);  // 没有参数的构造函数是默认构造函数, 初始化不会调用构造函数, 所以如果把"null"删掉, baseDMA a; 会报错, 但是写baseDMA a = baseDMA("hehe");是可以的
	baseDMA(const baseDMA & rs);  // 复制函数
	virtual ~baseDMA();  // 凡是有被继承可能的类都弄上虚析构函数, 就是仅仅浪费一点点空间和时间而已
	baseDMA & operator=(const baseDMA & rs);
	friend std::ostream & operator<<(std::ostream & os, const baseDMA & rs); // 友元输出函数
	// 这里使用友元的原因是想要用ostream对象访问本类的私有属性以达到输出的目的!!!!!!
};

// 一个继承了使用动态内存分配基类而自身没有使用动态内存分配的派生类
class lacksDMA : public baseDMA
{
private:
	enum {COL_LEN = 40};
	char color[COL_LEN];  // 没有使用动态内存分配的一个指针的(char *)方式保存字符串而是选择了字符数组的形式
public:
	lacksDMA(const char * c = "blank", const char * l = "null", int r = 0);
	lacksDMA(const char * c, const baseDMA & rs);
	friend std::ostream & operator<<(std::ostream & os, const lacksDMA & rs);  // 友元输出函数
};

// 基类使用了动态内存分配, 派生类也使用了的情况
class hasDMA : public baseDMA
{
private:
	char * style;  // 在构造函数为其使用动态内存分配
public:
	hasDMA(const char * s = "none", const char * l = "null", int r = 0);
	hasDMA(const char * s, const baseDMA & rs);
	hasDMA(const hasDMA & hs);  // 复制构造函数
	virtual ~hasDMA();
	virtual hasDMA & operator=(const hasDMA & rs);  // 赋值函数
	friend std::ostream & operator<<(std::ostream & os, const hasDMA & rs);
};

#endif