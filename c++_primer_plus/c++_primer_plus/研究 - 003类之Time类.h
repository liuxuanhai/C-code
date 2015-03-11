// p381开始 p398结束
// 时间的转换逻辑 运算符重载 友元函数
#ifndef Time类_H_
#define Time类_H_

class Time
{
private:
	int hours;
	int minutes;
public:
	Time();
	Time(int h, int m = 0);

	void AddMin	(int m);
	void AddHr	(int h);
	void Reset	(int h = 0, int m = 0);

/***************** 运算符重载 ******************/
	//Time Sum	(const Time & t) const;
		// 把上边的加法函数改成加法运算符重载
	Time operator + (const Time & t) const;
	Time operator * (const double) const;

/***************** 友元函数 **********************/  // 友元函数, (友元类, 友元函数成员)(第十五章);
	// 由于只能使用 对象 * double, 不能实现 double * 对象, 所以这里要使用友元函数实现
	// 创建友元函数:
	//		1. 放置原型的位置:	将其原型放在类声明中, 并在原型前面加上friend  --- 这样便意味着: 虽然这个函数是在类中声明的, 但他不是成员函数, 因此不能使用成员运算符来调用; 虽然函数不是成员函数, 但是他与成员函数的访问权限相同;
	//		2. 编写函数定义:	因为他不是成员函数, 所以不要使用Time::限定符, 另外, 不要再定义前面使用friend;
	// 对于 double * 对象, 在函数定义中直接return 对象 * double可以避开访问私有数据, 但是, 还是有以下理由说服我们:
	//		1. 友元函数可以直接让他作为正式类接口的组成部分 -- 如果不这样的话, 只能在类外边定义double * 对象, 因为*左边才是调用对象;
	//		2. 如果以后发现需要函数直接访问私有数据, 则只需修改函数定义, 不必修改类原型;
	friend Time operator * (const double db, const Time & t){return t * db;}

		// 关于重载 "<<" 运算符

	// 1. 要使Time类知道cout, 必须使用友元函数, 因为 cout << trip; 一个是ostream类, 一个是cout类, 如果使用 trip << cout, 会使人迷惑;
	// 2. 实现 cout << t << t; 应该返回cout对象的引用;
	// 3. 将友元放在cout对象的声明中也是可以的, 但是这样太麻烦又有风险;
	friend std::ostream & operator << (std::ostream & os, const Time & t);
/*************************************************/
	void Show	() const;
};

#endif