// 程序清单 4.20
#include <iostream>
#include <cstring>
int main()
{
	using namespace std;
	char animal[20] = "bear";
	const char * bird = "wren"; // "wren" 实际表示的是字符串的地址
	char ch = 'c';
	char * Ptr;
	char * ps;

	Ptr = &ch;
	// 直接写*Ptr = 'c';是不对的, 因为Ptr没有初始化, 所以他是个野指针
	cout << animal << " and " << bird << " and " << Ptr << endl;
	// cout输出字符串的时候使以一个字符的地址为参数的,
	// 只要是字符地址, 他就会试图去一直往下读知道遇见'\0'
	// 所以导致了Ptr的输出错误

	// cout << ps << endl; 使用野指针会导致程序终止 

	cout << "Enter a kind of animal: " << endl;
	cin >> animal;

	// cin >> ps; 这样使用野指针也会导致程序的终止
	// *ps = 'b'; 同样的 这样使用野指针也会导致程序的终止
	
	ps = animal;
	cout << ps << endl;

	cout << "Before using strcpy():\n";
	cout << animal << " at " << (int *)animal << endl;
	cout << ps << " at " << (int *)ps << endl;
	// 对输出类型进行了强制的类型转换 因为char类型的指针会被认作输出字符串, 所以强制转换成了指向int的指针

	ps = new char[strlen(animal) + 1]; // 在"堆"里面动态分配一个和用户输入的动物名一样打小的空间
	strcpy(ps, animal);
	cout << "After using strcpy():\n";
	cout << animal << " at " << (int *)animal << endl;
	cout << ps << " at " << (int *)ps << endl;

	cout << "*bird =" << bird << endl;
	// strcpy(bird, animal); 会报错, 因为const char * bird = "wrten";意思是bird的内容可以改变但是不可以通过它改变他指向内存的值
	// animal = bird; 同样不可以, 说明也不可能通过其他的指针修改"wrten", 进一步说明const char * bird = "wrten";指出"wrten"是不能修改的常量
	// const char * bird = "wrten"; 可以这样读:  >>常量字符<<指针 char const * bi = "ceshi"; 未定义的写法 char * const bi = "ceshi"; 读作: 字符>>指针常量<<
	//char * const bi = "ceshi";
	//bi = animal;是不允许的
	//bi = animal;
	//cout << "bi = " << bi << endl;
	//strcpy(animal, bird);//确实可以的
	cout << "*bird =" << bird << endl;

	delete [] ps;

	return 0;
}