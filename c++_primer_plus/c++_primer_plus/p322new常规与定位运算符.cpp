// 程序清单 9.10
// 注意在函数内部new的变量在该函数执行完后new的变量还存在, 但是在函数里面声明的指针会被销毁, 所以小心new的内存称为野内存
#include <iostream>
#include <new>  // for placement new (为定位new运算符提供原型)
const int N = 5;
const int BUF = 512;
char buffer[BUF];  // chunk(厚厚的一块) of memory
int main()
{
	using namespace std;
	double *pd1, *pd2;
	int i;
	cout << "Calling new and placement new:\n";
	pd1 = new double[N];  // use heap(堆)
	pd2 = new (buffer) double[N];  // use buffer array
	for (i = 0; i < N; i++)
		pd2[i] = pd1[i] = 1000 + 20.0 * i;
	cout << "Memory addresses:\n" << " heap: " << pd1
		<< " static: " << (void *) buffer << endl;  // buffer为char *类型, 不能显示其地址, 所以加上了void*
	cout << "Memory contents:\n";
	for (i = 0; i < N; i++)
	{
		cout << pd1[i] << " at " << &pd1[i] << ";\t";
		cout << pd2[i] << " at " << &pd2[i] << endl;
	}
	//delete [] pd2;   // 定点new分配(确切的说是选择)的内存不能用delete释放!!!!!!
					 // 确切的说是buffer指定的内存是静态内存, 而delete只能用于这样的指针: 指向常规new运算符分配的堆内存

	cout << "\nCalling new and placement new a second time:\n";
	double *pd3, *pd4;
	pd3 = new double[N];          // find new address
	pd4 = new (buffer) double[N];  // overwhrite old data
	for (i = 0; i < N; i++)
		pd3[i] = pd4[i] = 1000 + 40.0 * i;
	cout << "Memory contents:\n";
	for (i = 0; i < N; i++)
	{
		cout << pd3[i] << " at " << &pd3[i] << ";\t";
		cout << pd4[i] << " at " << &pd4[i] << endl;  // 由于上面没有释放pd2所以这里使用pd2也能达成跟使用pd4一样的效果
												  // 但是不能够释放pd2, 因为释放了pd2以后pd4就不能用了 所以释放语句是会导致程序异常终止的(释放的时候终止而不是使用pd4的时候终止)
	}

	cout << "\nCalling new and placement new a third time:\n";
	delete [] pd1;  // 释放内存, 防止野内存导致内存泄露
				   // 之所以放在这里而不是放在一使用完就释放的位置是因为使用完就释放的话后面的pd3就又会使用这个地址, 到时候跟第一次使用的地址对比不明显
	pd1 = new double[N];
	pd2 = new (buffer + N * sizeof(double)) double[N];
	for (i = 0; i < N; i++)
		pd2[i] = pd1[i] = 1000 + 60.0 * i;
	cout << "Memory contents:\n";
	for (i = 0; i < N; i++)
	{
		cout << pd1[i] << " at " << &pd1[i] << ";\t";  // 上面把pd1释放了一次, 然后再分配的时候又把同样的地址分配过来了, 但是这时候注意到pd3还没有释放, 而且pd3是比pd1后分配的, 但是在分配的时候却又在pd3前面分配了一个pd1, 这也说明了堆的内存管理方式
		cout << pd2[i] << " at " << &pd2[i] << endl;
	}
	delete [] pd1;
	delete [] pd3;

	return 0;
}