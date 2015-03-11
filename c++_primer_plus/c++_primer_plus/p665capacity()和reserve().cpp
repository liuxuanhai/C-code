#include <iostream>
#include <string>

int main()
{
	using namespace std;
	string empty;
	string small = "bit";
	string larger = "Elephants are a girl's best friend";
	cout << "Sizes:\n";
	cout << "\tempty: " << empty.size() << endl;
	cout << "\tsmall: " << small.size() << endl;
	cout << "\telarger: " << larger.size() << endl;
	cout << "Capacities:\n";
	cout << "\tempty: " << empty.capacity() << endl;  // 返回当前给内存块分配的空间的大小
	cout << "\tsmall: " << small.capacity() << endl;  // 本实现最小容量为十五个字符
	cout << "\telarger: " << larger.capacity() << endl;
	empty.reserve(50);  // 请求内存块的最小长度
	cout << "Capacity after empty.reserve(50): " << empty.capacity() << endl;
}