// 头文件<altorithm>中含有三个辅助函数, 一个用来在两值之间挑选较大者, 另一个在两值之间挑选较小者, 第三个用来交换两值
#include <algorithm>
using namespace std;

bool int_ptr_less(int * a, int * b)
{
	return *a < *b;
}

int main()
{
	int x = 17;
	int y = 42;
	int * px = &x;
	int * py = &y;
	int * pmax;

	pmax = std::max(px, py, int_ptr_less);	// px和py类型必须一致, 或者std::<long>(); 这样就明确了返回值的类型
}