//	创建: 2014-08-28 07:36:40
#include "08studentData.h"

std::string & StuBaseInfo::operator[](const string & key)
{
	// 如果已经存在, 返回实值引用
	for (auto pos = baseInfo.begin(); pos != baseInfo.end(); ++pos)
		if (pos->first == key)
			return pos->second;
	// 如果不存在, 增加字段, 默认设置新的实值为null
	baseInfo.push_back(std::make_pair(key, "null"));
	return baseInfo.back().second;
}

const std::string & StuBaseInfo::operator[](const string & key) const
{
	// 寻找是否存在
	for (auto pos = baseInfo.begin(); pos != baseInfo.end(); ++pos)
		if (pos->first == key)
			return pos->second;
	throw std::invalid_argument("不存在key值为" + key + "的基本信息!");
}

void StuGraInfo::updateTotalGra()
{
	auto t =	(currentCourse->second)[0] * 0.3 + 
		(currentCourse->second)[1] * 0.7;
	(currentCourse->second)[2] = t > 0 ? int(t + 0.5) : int(t - 0.5);	// 78.2 => 78    78.6 => 79		-1.3 => -1
}

StuGraInfo & StuGraInfo::operator[](const string & key)	
{
	// 如果已经存在, 将当前操作课程改成key指向的课程
	for (auto pos = graInfo.begin(); pos != graInfo.end(); ++pos)
	{
		if (pos->first == key)
		{
			currentCourse = pos;
			return *this;
		}
	}
	// 如果不存在, 那么增加课程, 默认成绩都是-1
	graInfo.push_back(std::make_pair(key, std::vector<int>(3, -1)));	// vector<int>(3, -1) 产生一个大小为3的vector, 每个都是-1
	currentCourse = graInfo.end() - 1;
	return *this;
}

const StuGraInfo & StuGraInfo::operator[](const string & key) const
{
	for (auto pos = graInfo.cbegin(); pos != graInfo.cend(); ++pos)
		if (pos->first == key)
			return *this;
}