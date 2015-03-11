// 注意: 定位new分配的内存不能用delete释放, 他只管分配就行了

#include <iostream>
#include <new>  // for 定位new运算符
using namespace std;

const int	N	= 5;
const int	BUF	= 512;
char		buffer[BUF];

int main(void)
{
	double * pd1, * pd2;

		// 第一次调用new和定位new

	cout << "调用new和定位new:\n";
	pd1 = new double[N];			// pd1 指向堆中分配的内存
	pd2 = new (buffer) double[N];	// pd2 指向buffer的首地址
	for (int i = 0; i < N; i++)
		pd2[i] = pd1[i] = 1000 + 20.0 * i;
	cout << "内存地址: \n" << "堆中 : " << pd1
		<< "   静态区: " << (void *)buffer << endl;  // 由于buffer指向的是字符串, 所以这里要转换成空指针才能使他显示指针而不是字符串
	cout << "内存中包含: " << endl;
	for (int i = 0; i < N; i++)
	{
		cout << pd1[i] << " at " << &pd1[i] << ";\t";
		cout << pd2[i] << " at " << &pd2[i] << endl;
	}

		// 第二次调用

	double * pd3, * pd4;

	cout << "\n第二次调用new和定位new:\n";
	pd3 = new double[N];			// 寻找新的堆内存
	pd4 = new (buffer) double[N];	// 覆盖原始数据
	for (int i = 0; i < N; i++)
		pd4[i] = pd3[i]= 1000 + 40.0 * i;
	cout << "内存中包括: \n";
	for (int i = 0; i < N; i++)
	{
		cout << pd3[i] << " at " << &pd3[i] << ";\t";

				// 这里将pd4改成pd2一样使用, 因为上面使用完了根本没有释放pd2, 而这两个是定位到了同一个位置
				// 但是这里是不能用完就释放pd2的, 释放了的话pd4怎么指向不存在的内存呢, 是吧, 但是编译器报错是在释放的时候报错而不是后知后觉的在使用pd4的时候才报错;
		cout << pd4[i] << " at " << &pd4[i] << endl;
	}

		// 第三次调用
	delete [] pd1;	// 释放内存, 防止野内存导致内存泄露
					// 之所以放在这里而不是放在一使用完就释放的位置是因为使用完就释放的话后面的pd3就又会使用这个地址, 到时候跟第一次使用的地址对比不明显
	cout << "\n第三次调用new和定位new:\n";

	pd1 = new double[N];
	pd2 = new (buffer + N * sizeof(double)) double[N];
	for (int i = 0; i < N; i++)
		pd2[i] = pd1[i] = 1000 + 60.0 * i;
	cout << "内存中包含:\n";
	for (int i = 0; i < N; i++)
	{
		cout << pd1[i] << " at " << &pd1[i] << ";\t";  // 上面把pd1释放了一次, 然后再分配的时候又把同样的地址分配过来了, 但是这时候注意到pd3还没有释放, 而且pd3是比pd1后分配的, 但是在分配的时候却又在pd3前面分配了一个pd1, 这也说明了堆的内存管理方式
		cout << pd2[i] << " at " << &pd2[i] << endl;
	}
	delete []pd1;
	delete []pd3;

	return 0;
}