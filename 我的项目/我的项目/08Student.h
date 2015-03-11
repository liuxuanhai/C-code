// ´´½¨: 2014-08-28 07:33:36
#ifndef STUDENT_H
#define STUDENT_H
#include "08studentData.h"
class Student
{
private:
	StuBaseInfo baseinfo;
	StuGraInfo	grainfo;

public:
	Student(std::string name);
	StuBaseInfo & getBaseInfo() { return baseinfo; }
	StuGraInfo  & getGrainfo() { return grainfo; }
	friend const Student & operator<<(std::ostream & os, const Student & stu);
	friend const Student & operator>>(std::istream & os, Student & stu);
};




#endif