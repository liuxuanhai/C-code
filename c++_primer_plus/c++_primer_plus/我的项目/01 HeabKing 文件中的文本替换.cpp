// Build: 2014-10-9 17:12:46

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include "HeabUtility.h"
using namespace std;

int main()
{
	string ItemKey =	"Rfxno;Itemcode;IsNewSoldListing;Confirmdate;";
						

	ifstream fin;
	fin.open("D:\\测试.txt");
	if (!fin.is_open())
	{
		cout << "没能打开文件!\n";
		exit(EXIT_FAILURE);
	}

	map<string, string> AItem;

		// 提取Item的Key	
	string temp = ItemKey;
	string getALable;
	fin >> getALable;	// 吃掉标题
	string tap;

	char t[10000];
	fin.getline(t, 10000);
	fin.getline(t, 10000);
	HString s(t, "\t");
	
	while (!s.isEnd())
	{
		cout << s.subStr() << endl;
	}
	//while (true)
	//{
	//	int ii;
	//	if ((ii = temp.find(";")) < 0)	// 提取结束
	//		break;

	//		// 从文件中读取一项
	//	fin >> getALable;

	//	cout << getALable;
	//	 //temp.substr(0, ii) << " ";      
	//	
	//	temp = temp.substr(ii + 1);		// 吃掉被提取的substr
	//}
}