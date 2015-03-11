// Build: 2014-10-12 11:17:19
// 总结: 标准答案跟我的差不多
// 流程图: 
// 
#include <iostream>
#include <vector>
using namespace std;
int ar[] = {1, 2, 2, 3, 3, 3, 3, 4, 5, 5, 6};

void myAnswer();
void standardAnswer();

int main()
{
	myAnswer();
	standardAnswer();
}

void myAnswer()
{
	vector<int> src(ar, ar + 10);

	int MI = 0;
	int C = 1;
	int N = 1;

	for (unsigned int i = 0; i < src.size() - 1; i++)
	{
		if (src[i] == src[i + 1])	// 如果发现有(>2)平台, 开始记录他的数量
			N++;
		else
		{
			if (N > C)
			{
				MI = i - N + 1;
				C = N;
				N = 1;
			}
			else
			{}
		}
	}

	cout << "我的方法: " << MI << endl;
}

void standardAnswer()
{
	int length = 1;
	int index = 0;
	for (int i = 1; i < 10; i++)
		if (ar[i] == ar[i - length])
			length++;
	cout << "书中方法: " << length;
}