// 程序清单 12.8
#include <iostream>
#include <string>
#include <new>  // 定位new
using namespace std;
const int BUF = 512;
class JustTesting
{
private:
	string words;
	int number;
public:
	JustTesting(const string & s = "Just Testing", int n = 0)
	{words = s; number = n; cout << words << " constructed\n";}
	~JustTesting(){cout << words << " ------------ destroyed\n";}
	void Show() const {cout << words << ", " << number << endl;}
};

int main(void)
{
{
	char * buffer = new char[BUF];  // 创建一个定位存储区
	JustTesting * pc1, * pc2;

	pc1 = new(buffer) JustTesting;  // place object in buffer 在定位存储区分配一段内存
	pc2 = new JustTesting("Heap1", 20);  // place object on heap 在堆里面分配一段内存

	cout << "Memory block addressed:\n" << "buffer: "
		<< (void *)buffer << "    heap: " << pc2 << endl;
	cout << "Memory contents:\n";
	cout << pc1 << ": ";
	pc1->Show();
	cout << pc2 << ": ";
	pc2->Show();

	JustTesting * pc3, * pc4;
	pc3 = new (buffer) JustTesting("Bad Idea", 6);  // 分配的地址与pc1一样!!!!!!!
	pc4 = new JustTesting("Heap2", 10);

	cout << "Memory contents:\n";
	cout << pc3 << ": ";
	pc3->Show();
	cout << pc4 << ": ";
	pc4->Show();

	delete pc4;  // 这里我没有写delete pc2然后显示的是没有------------ destroyed\n因为它位于动态分配的内存中, 所以不会再return上边的}上自动调用析构函数!!!
	//delete pc1; // 这里是不对的, 因为delete只能与常规new配合使用!!! 这样使用会在运行的时候卡死
	delete [] buffer;
	cout << "Done!";
}
	return 0;
}