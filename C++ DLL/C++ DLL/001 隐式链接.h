// Build: 2014-10-5 17:35:34
#ifndef HEABDLLEC
#define HEABDLLEC	extern "C" _declspec(dllimport)
#define HEABDLL		_declspec(dllimport)
#endif

HEABDLLEC int add(int a, int b);

class /*HEABDLL*/ Point	// 类的声明中不能加上extern "C"
{
public:
	void HEABDLL output(int x, int y);	// 包括类中的方法也不能使用extern "C"
	void input();
};