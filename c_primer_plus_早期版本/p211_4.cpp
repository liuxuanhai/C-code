 // 一个可以统计文本中单词数,字母数和平均每个单词的字母数的小程序
// c primer plus 编程练习 8.11 p211
#include <stdio.h>
#include <ctype.h>

int get_num_letters (char cr);  // 求字母数函数原型
int get_num_words (char cr);    // 求单词数函数原型

// 自定义函数中不能在while循环中初始化的东西
int n_l;                        // 参与到while()循环的千万别忘了初始化计数器 // 但是不能再循环里面初始化
int n_w = 0;
int is_word = 0;                // 判断单词的标志 开始为0,从读取单词到结束之前为1,读完了恢复为0

int main (void)
{
	char ch;             // 字符流中的每个字符
	int num_letters = 0; // 单词数
	int num_words = 0;   // 字母数
	float avg = 0;           // average 平均数

	printf ("请给我一段文本(在行的开始输入|结束我): \n");
	while ((ch = getchar()) != '|')
	{   
		num_letters = get_num_letters (ch);
		num_words = get_num_words (ch);
	}
	avg = (float)num_letters / (float)num_words;  // 类型转换
	printf ("一共有%d个字母,%d个单词,平均"
		    "每个单词%.2f个字母.\n",
			num_letters, num_words, avg);

	return 0;
}

int get_num_letters (char cr)
{
	

	if (isalnum(cr))                        // 如果是一个字母或数字
		n_l++;				
	
	return n_l;
}

int get_num_words (char cr)
{


	if (isalnum(cr))                     
		is_word = 1;                     
	if (1 == is_word && isspace(cr))        // 在一个单词的最后一个字母和空格的交汇处为n_w加1
	{	
		n_w++;
		is_word = 0;                        // 防止在一个单词后的连续两个空格中间又判断为一个单词 
	}
	
	return n_w;
}