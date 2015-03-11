// 创建: 2014-08-20 14:17:19
// map的元素是成对的键值/实值(key/value)

#include <iostream>
#include <map>
#include <string>

// multimap不允许我们使用subscript(下标)操作符, 因为multimap允许单一索引对应多个不同的元素, 而下标操作符却只能处理单一实值
// 由于map的所有键值都是独一无二的, 我们可以把它视为一个关联式数组
// 关联式数组: 以键值为索引, 键值可以使任意型别.

#define MAP
//#define MULTIMAP

int main()
{
#ifdef MAP
	
	typedef std::map<std::string, float> StringFloatMap;
	StringFloatMap coll;

	// insert some elements into the collection
	coll["VAT"] = 0.15f;
	coll["Pi"] = 3.1415f;
	coll["an arbitrary number"] = 4983.223f;
	coll["Null"] = 0;
	// coll.insert("kkkkkk", 1.23f);	// ERROR # 1

	// print all elements
	// - iterator over all elements
	// - element member first is the key
	for (StringFloatMap::iterator pos = coll.begin(); pos != coll.end(); ++pos)
		std::cout	<< "key: \"" << pos->first << "\" "
					<< "value: " << (*pos).second << std::endl;

	using namespace std;
	cout << endl << endl;
	cout << "coll[\"Pi\"] = " << coll["Pi"] << endl;	// !!!!!!!!!!!!!! 这不就是php中的..........

#elif defined MULTIMAP
	
	// type of the collection
	typedef std::multimap<int, std::string> IntStringMMap;

	IntStringMMap coll;

	// insert some elements in arbitrary order
	// - a value with key 1 gets inserted twice
	coll.insert(std::make_pair(5, "tagged"));
	coll.insert(std::make_pair(2, "a"));
	coll.insert(std::make_pair(1, "this"));
	coll.insert(std::make_pair(4, "of"));
	coll.insert(std::make_pair(6, "strings"));
	coll.insert(std::make_pair(1, "is"));
	coll.insert(std::make_pair(3, "multimap"));
	//coll.insert(7, std::string("777777"));	// ERROR # 2

	// print all element values
	// - iterate over all elements
	// - element member second is the value
	IntStringMMap::iterator pos;
	for (pos = coll.begin(); pos != coll.end(); ++pos)
		std::cout << pos->second /*(*pos).second*/ << ' ';	// pos->second 取出pair的第二个成员
	std::cout << std::endl;

	//std::cout << std::endl << std::endl;
	//std::cout << coll[3] << std::endl;	// multimap 无法被当作关联数组..........
#endif

	std::map<std::string, std::string> temp;
	//temp.insert(std::string("124"), string("1212"));	// EORROR # 3
	//cout << endl << endl << temp.begin()->first << temp.begin()->second << endl;

	temp["he"] = "shixiong";
	temp.insert(make_pair("da", "xiong"));
	std::map<std::string, std::string> & temp2 = temp;
	cout << endl << endl << temp2["da"] << endl;
}