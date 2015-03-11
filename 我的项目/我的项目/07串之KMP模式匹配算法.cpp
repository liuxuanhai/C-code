// 克努特-莫里斯-普拉特算法 简称 KMP算法
#define KMP

#ifndef KMP
	
	// 蛮力算法完成字符串的匹配

#include <iostream>
int main(void)
{
	char * str = "daxionggege";
	char cinStr[100] = {0};
	std::cin >> cinStr;

	// 开始蛮力比较
	char * temp = str;
	while(temp)
	{
		int i;
		for (i = 0; temp[i] && cinStr[i] && temp[i] == cinStr[i]; i++)
		{
			std::cout << temp[i];
		}
		if (!cinStr[i])	// 如果是遍历了输入, 则说明成功匹配
		{
			std::cout << "存在";
			return 0;
		}
		temp++;
	}

	std::cout << "不存在";
	return 0;
}

#else

#include <iostream>
using namespace std;

void get_next(string T, int *next);
int  Index_KMP(string S, string T, int pos);

int main(void)
{


	return 0;
}

void get_next(string T, int *next)
{
	int i = 1, j = 0;
	next[1] = 0;
	while (i < T[0])	// 此处T[0]表示字符串T的长度
	{
		if (0 == j || T[i] == T[j])	// T[i] 表示后缀的单个字符
									// T[j] 表示前缀的单个字符
		{
			i++;
			j++;
			next[i] = j;
		}
		else
			j = next[j];	// 若字符不相同, 则j值回溯
	}
}

int  Index_KMP(string S, string T, int pos)
{
	int i = pos;	// i 用于主串S当前位置下标值, 若pos不为1, 则从pos位置开始匹配
	int j = 1;		// j 用于子串T中当前位置下标值
	int next[255];	// 定义一个 next 数组
	get_next(T, next);	// 对串 T 做分析, 得到next数组
	while (i <= S[0] && j <= T[0])	// 若i小于S的长度且j小于T的长度时, 循环继续
	{
		if (0 == j || S[i] == T[j])	// 两个字母相等则继续, 与朴素算法增加了 j = 0判断
		{
			i++;
			j++;
		}
		else	// 指针后退重新开始匹配
		{
			j = next[j];	// j退回合适位置, i值不变
		}
	}
	if (j > T[0])
		return i - T[0];
	else
		return 0;
}

#endif