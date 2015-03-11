// 编程练习 9.6 (3)
// 创建两个结构的缓冲区
#include <iostream>
#include <new>
using namespace std;
struct chaff
{
	char dross[20];
	int slag;
};
int main()
{
	chaff * stPtr1;
	chaff * stPtr2;
	stPtr1 = new chaff[2];
	stPtr2 = new (stPtr1) chaff[2];
	strncpy(stPtr2->dross, "I'm chaff one.", 20);  // 如果源字符串大于20个将无法复制空字符
	strncpy((stPtr2 + 1)->dross, "I'm chaff two.", 20);
	stPtr2->slag = 111;
	(stPtr2 + 1)->slag = 222;

	for (int i = 0; i < 2; i++)
		cout << stPtr2[i].dross << endl << (stPtr2 + i)->slag << endl;
	delete [] stPtr1;

	return 0;
}