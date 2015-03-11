// Build: 2014-10-10 12:12:33

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct item
{
	std::string key;
	std::string value;
};

int findItem(vector<item> & source, string t);

int main(void)
{
	ifstream fs;
	fs.open("D:\\Test.txt");
	if (!fs.is_open())
	{
		cout << "没能打开文件!\n";
		exit(EXIT_FAILURE);
	}

	item it;
	vector<item> tra;

	fs >> it.key;
	while (fs.good())
	{
		// 吃掉注释行
		if (it.key[0] == '=')
		{
			while (fs.get() != '\n');
			fs >> it.key;
		}

		cout << it.key << " ";
		fs >> it.value;
		cout << it.value << endl;
		tra.push_back(it);
		
		fs >> it.key;
		
	}

	ifstream fin;
	fin.open("D:\\测试.txt");
	if (!fin.is_open())
	{
		cout << "没能打开文件!\n";
		exit(EXIT_FAILURE);
	}

	ofstream fout;
	fout.open("D:\\测试2.txt");

	char tt[10000];
	fin.getline(tt, 10000, '\t');
	std::string t = tt;
	while (fin.good())
	{
		if (t.size() > 0 && t.at(0) == '\n')
			t.assign(t.begin() + 1, t.end());

		int index;
		if ((index = findItem(tra, t)) == -1)
			fout << t;
		else
			fout << tra[index].value;

		fout << "\t";

		fin.getline(tt, 10000, '\t');
		t = tt;
	}
}

int findItem(vector<item> & source, string t)
{
	for (unsigned int i = 0; i < source.size(); i++)
	{
		if (source[i].key == t)
			return i;
	}
	return -1;
}