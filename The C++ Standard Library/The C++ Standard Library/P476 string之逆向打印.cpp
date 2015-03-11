#include <iostream>
#include <string>
using namespace std;

int main(int argc, char ** argv)
{
	const string delims(" \t,.;");	// 所有间隔符被定义于一个特殊字符串常数中
	string line;

	// for every line read succesfully
	while (getline(cin, line))
	{
		string::size_type begIdx, endIdx;

		// search beginning of the first word
		begIdx = line.find_first_not_of(delims);
			// 搜寻第一个单词的其实位置, 函数find_first_not_of()返回"不隶属参数所指字符串"的第一个字符的索引, 如果没有找到, 返回string::npos	

		// while beginning of a word found
		while (begIdx != string::npos)	// 如果找到了一个单字, 进入内层循环
		{
			// search end of the actual word
			endIdx = line.find_first_of(delims, begIdx);	// 用来搜寻第一个参数所指字符串内的任何字符的第一次出现位置, 第二个参数是可选的, 用来标示搜寻起点
			if (endIdx == string::npos)
				// end of word is end of line
				endIdx = line.length();

			// print characters in reverse order
			// 将所有字符逆序打印
			for (int i = endIdx - 1; i >= static_cast<int>(begIdx); --i)
				cout << line[i];	// 如果忘记把begIdx转型为int, 程序可能进入无穷循环中, 甚至崩溃掉, 

		cout << ' ';

		// search beginning of the next word
		begIdx = line.find_first_not_of(delims, endIdx);	// 重新初始化begIdx, 使他标示下一个单词的起点(如果有下一个单词的话)
		}
		cout << endl;
	}
}