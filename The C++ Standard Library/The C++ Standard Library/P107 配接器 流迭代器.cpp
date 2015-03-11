// 创建: 2014-08-21 13:43:55
// 流迭代器: 一种用来读写stream的迭代器, 提供了必要的抽象性, 使得键盘的输入像是个群集, 你能从中读取内容;

// 程序: 从标准输入读取所有输入文字, 排序, 将它们打印于屏幕
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
	vector<string> coll;
	// read all words from the standard input
	// - source: all strings until end-of-file(or error)
	// - destination: coll(inserting)
	copy(istream_iterator<string>(cin),	// start of source	// 产生一个可从"标准输入流cin"读取数据的stream iterator, <string>表示专门读取这种型别的元素, 这些元素通过operator>>被读取进来, 因此当算法企图处理下一个元素时, Istream iterators就会将这种企图转化为以下行动: cin >> string;
		istream_iterator<string>(),		// end of source	// 调用Istream iterators的default构造函数, 产生一个代表"流结束符号"的迭代器, 它代表的意义是: 你不能再从中读取任何东西
		back_inserter(coll));			// destination

	// sort elements
	sort(coll.begin(), coll.end());

	// print all elements without duplicates(复制, 加倍, 重复)
	// - source: coll
	// - destination: standard output(without newline between elements)
	unique_copy(coll.begin(), coll.end(),		// unique_copy不会copy重复值
		ostream_iterator<string>(cout, "\n"));	// 产生一个output stream iterator, 透过operator<<向cout写入string, cout之后的第二个参数(可有可无)被用来作为元素之间的分隔符 
}