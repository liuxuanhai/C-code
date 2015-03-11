#include <iostream>
using namespace std;
int main(void)
{
	char strAr[] = "daxiong";  // 这里不是一个指向他的指针, 而是将字面值"daxiong"赋给了strAr数组, 这样就能对他使用cin>>了;
	char * pStr = "heshixiong";  // 这里必须加上const, 而且加上了的话会在编译前对cin>>进行报错;

	cout << strAr << endl
		<< pStr << endl;
	cin >> strAr;
	cout << strAr << endl;
	cin >> pStr;  // 这里会导致程序崩溃, 因为"heshixiong"是一个字面值, 他在代码中不管出现多少次都是唯一一段内存保存的, 所以pStr不能改变他, 这样会将其他的也给改了, 所以声明的时候必须加上const;
	cout << pStr << endl;

	return 0;
}
