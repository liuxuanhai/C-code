// p411开始 p426结束

// 只有一个参数的构造函数可以称之为 转换函数(将数据转换成对象)
// 还有将对象转换成其他数据的类方法	转换函数(将对象转换成数据)

// 类的自动类型转换和强制类型转换
#ifndef 单位转换类_H_
#define 单位转换类_H_

class Stonewt
{
private:
	enum{Lbs_per_stn = 14};	// 每英石多少磅
	int		stone;			// 英石
	double	pds_left;		// 英镑的小数部分
	double	pounds;			// 整个英镑数
public:

/******************* 构造转换函数 ************************/

	/*explicit*/ Stonewt(double lbs);	// 转换函数, 因为int能按照c++内置的转换规则转换成double, 所以int等类型也可以用作参数, 首先转换成double, 然后转换成对象
		// explicit关闭隐式转换, 但是仍然允许显示转换
			// obj_stonewt = 19.6;	// 如果explicit了, 这将会不允许
			// obj_stonewt = Stonewt(19.6);	// ok, 显式的类型转换
			// obj_stonewt = (Stonewt)19.6;	// ok, 老式显示类型转换

/******************* 类方法转换函数 **********************/
	// 1. 必须是类方法
	// 2. 不能指定返回值	-- 比如operator double() 他的double已经指定了返回类型 
	// 3. 不能有参数		-- 调用他的对象就是他的参数, 所以不用指定参数
	// 4. 如果只定义了一个转换函数的话, 那么编译器将会支持隐式转换  --  如果只定义了double() 那么cout << obj_stonewt将会隐式将obj_stonewt转换成double
	// 5. 类方法转换函数同样可以加上explicit, 表明只支持显示类型转换
	operator double(){return pounds;}
	operator int(){return int(pounds + 0.5);}
/*********************************************************/



	Stonewt(int stn, double lbs);
	Stonewt();
	~Stonewt();

	void show_lbs() const;	// 以英镑为单位显示重量
	void show_stn() const;	// 以英石和英镑为单位显示重量
};

#endif