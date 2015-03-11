#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

const char * FILENAME = "04计算代码数量测试.cpp";

int main(void)
{
		// 打开文件, 错误检查

	ifstream fin;	// 文件输入对象
	fin.open(FILENAME);
	if (!fin.is_open())
	{
		cout << "不能打开文件 " << FILENAME << " !\n";
		exit(EXIT_FAILURE);
	}
	cout << "打开文件 " << FILENAME << " 成功...\n";
	cout << "读取文件 " << FILENAME << " 开始统计...\n\n";

		// 读取文件, 进行统计
	char	ch;				// 临时保存每个读取的字符
	struct
	{
		int		iCntChar;	// 字符数(不显示的回车除外, 注释除外, 空白符(空格, tap)除外)
		int		iCntLetter;	// 字母数((不显示的回车除外, 注释除外))
		int     iCntFuHao;	// 符号数(, ; / * () {} & ...)
		int		iCntRow;	// 行数
		int		iDigit;		// 阿拉伯数字个数
		int		iCnHalf;	// 非注释中文个数(字符串, 或者手贱定义的宏(#define 测试), 或者...)
		int		iCnHalfAnt;	// 注释中文个数
		int		iCntCharAnt;// 注释字符个数(回车符除外, 包含空白符(空格, tap算一个字符)
	} Data = {0};
	enum annotation{ifAnt, isAnt, notAnt, isAnt2};
	annotation	Ant = notAnt;	// 注释判断
		// 开始统计

	ch = fin.get();	
	int chNum = 0;
	while (fin.good())
	{
		if (chNum++ >= 100000)
		{
			std::cout << "文件" << FILENAME << "不是标准c/c++/h的文件, 程序退出";
			exit(EXIT_FAILURE);
		}
			// 中文处理

		if ((ch > 255 || ch < 0) 
			&& isAnt != Ant && isAnt2 != Ant)	// 排除中文注释
		{
			ch = fin.get();
			Data.iCnHalf++;
			continue;
		}

			// 统计行数
		if (ch == '\n')
			Data.iCntRow++;

			// 处理注释 "//"
		if ('/' == ch && notAnt == Ant)	// "//" ? "/" ? "/*" ? "*/"
			Ant = ifAnt;
		else if ('/' == ch && ifAnt == Ant)
			Ant = isAnt;
		else if (isAnt == Ant)
		{
			int flag = 0;
			do{	// 使用do-while使得 "//"后边的第一个字符也能接受判断
				if (ch == EOF)
				{
					flag = 1;
					break;
				}
				if (ch < 0 || ch > 255)
					Data.iCnHalfAnt++;
				else
					Data.iCntCharAnt++;
			}while('\n' != (ch = fin.get()));	// 吃掉注释
			Data.iCntCharAnt += 2;	// "//"符号也算两个注释字符

			if (flag)
				break;
			Data.iCntRow++;	// 吃了这行的注释, 但是行数还是得加上
			Ant = notAnt;
			
		}

			// 处理注释 "/* */"
		else if ('*' == ch && ifAnt == Ant)
			Ant = isAnt2;
		else if (isAnt2 == Ant)
		{
			Ant = notAnt;
			int flag = 0;	// 寻找 "*/" 的标记
				
				// 一直删除注释, 直到注释结束
			
			do{	// 防止/*后边的第一个字符被忽视, 而且不用do-while的话, /**/会出错
				if (ch < 0 || ch > 255)
					Data.iCnHalfAnt++;
				else if ('*' == ch)
				{
					flag = 1;
					Data.iCntCharAnt++;
				}
				else if (flag && '/' == ch)
					break;
				else
				{
					if ('\n' == ch)	// 注释的行数也算行数, 但是不算注释字符
						Data.iCntRow++;
					else
						Data.iCntCharAnt++;
					flag = 0;
				}
			} while (ch = fin.get());
			Data.iCntCharAnt += 3;	// "/*", '/'
		}

			// 统计字符, 字母个数
		else if (isgraph(ch))	// 字符
		{
			Ant = notAnt;
			Data.iCntChar++;
			if (isalpha(ch))	// 字母个数
				Data.iCntLetter++;
			else if (ispunct(ch))	// 符号数量
				Data.iCntFuHao++;
			else if (isdigit(ch))	// 数字个数
				Data.iDigit++;	
		}
		ch = fin.get();
	}

		// 进行输出显示

	cout << "\n统计文件 "		<< FILENAME						<< " 完毕...\n";
	cout << " 行数 : "			<< ++Data.iCntRow					<< endl;
	cout << "总字符: "			<< Data.iCntChar + Data.iCnHalf / 2 + Data.iCntCharAnt + Data.iCnHalfAnt / 2 << endl;
	cout << "\t非注释字符数: "	<< Data.iCntChar + Data.iCnHalf / 2		<< endl;
	cout << "\t\t字母数: "		<< Data.iCntLetter					<< endl;
	cout << "\t\t符号数: "		<< Data.iCntFuHao					<< endl;
	cout << "\t\t数字数: "		<< Data.iDigit						<< endl;
	cout << "\t\t中文数: "		<< Data.iCnHalf / 2					<< endl;
	cout << "\t注释字符数: "	<< Data.iCntCharAnt + Data.iCnHalfAnt / 2	<< endl;
	cout << "\t\t中文数: "		<< Data.iCnHalfAnt / 2				<< endl;
	cout << "\t\t字符数: "		<< Data.iCntCharAnt					<< endl;

	cout << "\nDone!\n";
	return 0;
}