#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
	// create empty vector for strings
	vector<string> sentence;
	
	// reserve memory for five elements to avoid reallocation	avoid 消除, 避免 reallocation 再分配
	sentence.reserve(5);	// 此时sentence依旧是一个empty容器

	// append(加入) some elements
	sentence.push_back("Hello");
	sentence.push_back("how");
	sentence.push_back("are");
	sentence.push_back("you");
	sentence.push_back("?");

	// print elements separated(被分开) with spaces
	copy(sentence.begin(), sentence.end(), ostream_iterator<string>(cout, " "));
	cout << endl;

	// print "technical data"
	cout << " max_size(): " << sentence.max_size() << endl;
	cout << " size(): " << sentence.size() << endl;			// 5
	cout << " capacity(): " << sentence.capacity() << endl;	// 5

	// swap second and fourth element
	swap(sentence[1], sentence[3]);

	// insert element "always" before element "?"
	sentence.insert(find(sentence.begin(), sentence.end(), "?"), "always");

	// assign "!" to the last element
	sentence.back() = "!";

	// print elements separated with spaces
	copy(sentence.begin(), sentence.end(), ostream_iterator<string>(cout, " "));
	cout << endl;

	// print "technical data" again
	cout << " max_size(): " << sentence.max_size() << endl;
	cout << " size(): " << sentence.size() << endl;			// 6
	cout << " capacity(): " << sentence.capacity() << endl;	// 7	// 这里C++多给预留了1个元素内存大小, 在不同的实现上不同, 书中多余留了4个元素内存大小

	cout << endl;

	vector<int> v1(2);
	v1[0] = 0;
	v1[1] = 1;
	cout << v1.capacity() << endl;
	v1.push_back(2);
	cout << v1.capacity() << endl;
	v1.insert(v1.begin(), v1.begin(), v1.end());
	cout << v1.capacity() << endl;	// 这里一直不肯多给预留
}