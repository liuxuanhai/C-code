// 创建: 2014-08-06
#include <iostream>
using namespace std;
namespace Ui { typedef int A; }
typedef double A;
typedef A AA;
namespace Ui{ typedef AA B; }	// 这里想要使用外部A就把外部A定义成AA然后在这里使用AA把
int main()
{
	Ui::B temp = 2.34;
	cout << temp << endl;
}