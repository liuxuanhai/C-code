// 创建: 2014-08-21 16:43:16

#include <iostream>

// PRINT_ELEMENTS()
// - prints optional(可选的, 随意的) C-stirng optcstr(opt, 选择) followed by
// - all elements of the collection coll
// - separated by spaces
template<class T>
inline void PRINT_ELEMENTS(const T & coll, const char * optcstr = "", const char * s = "\n")
{
	typename T::const_iterator pos;	// typename T::const_iterator 指明后边的是一个类型而不是一个值
	std::cout << optcstr;
	for (pos = coll.begin(); pos != coll.end(); ++pos)
		std::cout << *pos << " ";
	std::cout << s;
}