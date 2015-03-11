// C:\Users\daxiong\Desktop\新建文件夹\1.exe prog.dat mydir hello. oops.tmp end.dat
#include <iostream>
#include <string>	// string 对象的字符串尾部没有一个特殊字符 '\0'
using namespace std;

int main(/*int argc, char ** argv*/)
{
	int argc = 6;
	char *argv[6] = {
		"C:\\Users\\daxiong\\Desktop\\新建文件夹\\1.exe",
		"prog.dat", "mydir", "hello.", "oops.tmp", "end.dat"
	};
	string filename, basename, extname, tmpname;
	const string suffix("tmp");	// suffix 填后缀, 后缀, 下标

	// for each command-line argument
	// (which is an ordinary C-string)
	for (int i = 0; i < argc; ++i)
	{
		// process argument as file name
		filename = argv[i];
		// search period in file name	// period 周期, 句点
		string::size_type idx = filename.find('.');	// 搜寻失败返回 string::npos
		if (idx == string::npos)	// 如果字符串里面没有'.'符号
			// file name does not contain any period
			tmpname = filename + '.' + suffix;
		else
		{
			// split(分开, 分离, 分割) file name into base name and extension(延长)
			// - base name contains all characters before the period
			// - extension contains all characters after  the period
			basename = filename.substr(0, idx);	// arg1 起点索引 arg2 字符个数
				// arg2 字符个数可以为任意值, 如果大于剩余字符数, 则剩余字符都会被返回	

			extname  = filename.substr(idx + 1);// 从 arg1 开始, 将剩余字符都返回
			if (extname.empty())	// 处理 "hello."
			{
				// caontains period but no extension: append tmp
				tmpname = filename;
				tmpname += suffix;
			}
			else if (extname == suffix)	// 处理 "oops.tmp"
			{
				// replace extension tmp with xxx
				tmpname = filename;
				tmpname.replace(idx + 1, extname.size(), "xxx");	// arg1 起点索引 arg2 字符个数  arg2可以为任意值, 如果大于实际剩余字符数, 则所有剩余字符都会被用到
					// string::size()返回字符串的字符个数 string::length()可以获得相同结果
					// 这两个函数依不同的设计原则执行了相同的动作, length()传回字符串的长度, 就好像C-strings以strlen()所得结果一样, size()则是根据STL习惯而设置的成员函数, 用来表明元素数量
			}
			else	// 处理 "end.dat"
			{
				// replace any extension with tmp
				tmpname = filename;
				tmpname.replace(idx + 1, string::npos, suffix);
					// 如果使用string::npos相当于指明"使用所有字符"
			}	
		}
		// print file name and temporary name
		cout << filename << " => " << tmpname << endl;
	}
	string a;
	cin >> a;
}
// 凡是"以一个索引和一个字符长度作为参数"的地方, 字符串行为遵循下面两个规则:
//		1. 索引值必须合法, 该值必须小于字符串的字符个数(第一个字符的索引是0), 最后一个字符的下一个位置(的索引)可用来表明结束位置  大部分情况下, 如果指定的索引超过了实际字符数, 就会引发out_of_range异常, 不过, 用以搜寻单一字符或者某个位置的所有搜寻函数, 均可接收任意索引, 如果索引超过了实际字符数, 这些函数就会返回string::npos(表示没有找到)

//		2. 字符数量(长度)可以为任意值, 如果其值大于实际剩余的字符数, 则这些剩余字符都会被用到, 如果使用string::npos, 相当于"剩余所有字符"
//		eg: 如果找不到'.', 以下表达式会抛出异常, filename.substr(filename.find('.')), 但是以下表达式不会抛出异常, 而是返回整个文件名filename.substr(0, filename.find('.'))