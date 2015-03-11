// Build: 2014-10-10 12:12:33
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>
#include "HeabUtility.h"
using namespace std;

struct item
{
	string	key;
	int		value;
};

void openHowChangeFile(vector<item> & tra);
int isChangeItem(vector<item> & tra, string s);


int main()
{
	char buf[10000];
	ifstream fin;

			// 打开转换标准文档, 读取其内容

	vector<item> tra;
	openHowChangeFile(tra);
	
			// 打开source文档, 进行操作

	fin.open("测试.txt");
	if (!fin.is_open())
	{
		cout << "无法打开文件 测试.txt\n";
		exit(EXIT_FAILURE);
	}

	ofstream fout;
	sprintf_s(buf, "%d.txt", time(nullptr));
	fout.open(buf);

		// 读取一行
	fin.getline(buf, 10000);
	HString hs(buf, "\t");
	while (fin.good())
	{
			// 输出到文件
		int index;
		while (!hs.isEnd())
		{
			string elem = hs.subStr();
			
			// 如果转换标准文件中指定的更改项, 则更改, 否则直接输出
			if ((index = isChangeItem(tra, elem)) != -1)	// 如果是要更改的
				fout << tra[index].value << "\t";
			else											// 如果是不用更改的
				fout << elem << "\t";					
		}
		fout << "\n";
			// 读取下一行
		fin.getline(buf, 10000);
		hs.reset(buf, "\t");
	}
}

void openHowChangeFile(vector<item> & tra)
{
	ifstream fin;
	item it;

	fin.open("Test.txt");
	if (!fin.is_open())
	{
		cout << "无法打开文件Test.txt\n";
		exit(EXIT_FAILURE);
	}

	fin >> it.key;
	while (fin.good())
	{
		// 吃掉注释行
		if (it.key[0] == '=')
		{
			while (fin.get() != '\n');
			fin >> it.key;
		}
		fin >> it.value;
		tra.push_back(it);
		fin >> it.key;
	}

	fin.close();
}

int isChangeItem(vector<item> & tra, string s)
{
	for (unsigned int i = 0; i < tra.size(); i++)
	{
		if (tra.at(i).key == s)
			return i;
	}
	return -1;
}