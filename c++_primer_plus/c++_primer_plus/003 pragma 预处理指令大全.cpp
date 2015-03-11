// 建立: 2014-8-18 19:42:46

// #pragma para
// 1. message	参数	在编译信息输出窗口输出相应的信息 eg: 检查宏的存在性
// 2. code_seg	参数	它能够设置程序中函数代码中存放的代码段, 开发驱动程序的时候会用到 #pragma code_seg(["section-name"["section-class"]])
// 3. once		参数	只要在头文件的最开始处加入这条指令就能够保证头文件被编译一次, 考虑到兼容性和#ifndef 宏 的更加安全性, 他不常用了
// 4. hdrstop	参数    表示预编译头文件到此为止, 后面的头文件不进行预编译, BCB可以预编译头文件以加快链接的速度. 有时单元之间有依赖关系, 比如单元A依赖单元B, 所以单元B要先于单元A编译, 可以用#pragma startup指定编译优先级, 如果使用了#pragma package(smart_init), BCB就会根据优先级的大小先后编译
// 5. resource "*.dfm"	把*.dfm文件中的资源加入工程, *.dfm中包括窗体外观的定义
// 6. warning(disable: 4507 34; once: 4385; error: 164)
	// #pragma warning(disable: 4507 34) 不显示4507和34号警告信息
	// #pragma warning(once: 4385) 4385号警告信息只显示一次
	// #pragma warning(error: 164) 把164号警告信息作为一个错误
	// #pragma warning(push, n) #pragma warning(pop)等不解释了....
// 7. comment	参数	将一个注释记录放入一个对象文件或可执行文件中 eg: #pragma (lib, "winmm.lib")
// 8. #pragma loop_opt(on)	激活循环优化功能 #pragma loop_opt(off)	终止
// ...

#include <iostream>
using namespace std;

#define MESSAGE

int main()
{
	// 1
#ifdef MESSAGE
#pragma message("预处理指令中定义了MESSAGE宏!")
#endif

	int iTemp = 0.23;

	// 6
#pragma warning(disable: 4244)	// 从这一行开始, 后边的4244号警告全部不显示
	int itemp = 1.23;	// warning C4244: “初始化”: 从“double”转换到“int”，可能丢失数据

	
}