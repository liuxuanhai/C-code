// 创建: 2014-08-21 20:20:53
#ifndef	STUDENTDATA_H
#define STUDENTDATA_H
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <stdexcept>
class StuBaseInfo
{
	typedef std::string string;
public:
	typedef std::vector<std::pair<std::string, std::string> > baseInfoVector;
private:
	baseInfoVector baseInfo;

public:
	StuBaseInfo() {}
	virtual ~StuBaseInfo() {}

	string & operator[](const string & key);	// 使用baseInfo["name"] = "daxiong", 如果存在字段"name"这将是更改, 否则是添加
	const string & operator[](const string & key) const;
	auto begin()->decltype(baseInfo.begin()) { return baseInfo.begin(); }
	//decltype(baseInfo.begin()) end() { return baseInfo.end(); }	// error C2228: “.begin”的左边必须有类/结构/联合 ?????
	auto end()->decltype(baseInfo.end()) { return baseInfo.end(); }
	auto cbegin()->decltype(baseInfo.cbegin()) { return baseInfo.cbegin(); }
	auto cend()->decltype(baseInfo.cend()) { return baseInfo.cend(); }
};

class StuGraInfo
{
private:
	typedef std::string string;
public:
	typedef std::vector<std::pair<string, std::vector<int>>> graInfoType;	// int[3]: (0)平时成绩 (1)卷面成绩 (2)综合成绩(3:7)
private:
	graInfoType graInfo;
	graInfoType::iterator currentCourse;	// 指向当前课程
		// 初始化为值为null, 会自动更新为最新添加的课程
		// ordinaryGra(), examGra(), totalGra()分别返回当前课程的相应成绩

	void updateTotalGra();

public:
#pragma message("这里的初始化没有完成呢 StuGraInfo() { currentCourse = null; }")//StuGraInfo() { currentCourse = null; }
	~StuGraInfo() {}

	StuGraInfo & operator[](const string & key);	// Stu["数学"]指明当前操作课程是数学, 如果课程不存在将创建(成绩都是-1)	
	const StuGraInfo & operator[](const string & key) const;
	// 返回对象是为了实现 Stu["数学"].ordinaryGra()这样的调用
	int & ordinaryGra()				{ updateTotalGra(); return (currentCourse->second)[0]; }
	int & examGra()					{ updateTotalGra(); return (currentCourse->second)[1]; }
	const int & ordinaryGra() const	{ return (currentCourse->second)[0]; }
	const int & examGra() const		{ return (currentCourse->second)[1]; }
	const int & totalGra() const	{  return (currentCourse->second)[1]; } // 综合成绩计算而来, "只读"
	// 为了实现连续赋值 stu["数学"].ordinaryGra(100).examGra(98);
	StuGraInfo & ordinaryGra(int n) { (currentCourse->second)[0] = n; return *this; }
	StuGraInfo & examGra(int n)		{ (currentCourse->second)[1] = n; return *this; }

	auto begin()->decltype(graInfo.begin()) { return graInfo.begin(); }
	auto end()->decltype(graInfo.end())		{ return graInfo.end(); }
};


#endif