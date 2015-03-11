#include <iostream>
using namespace std;
#define NO 2
#define PRINT(x) printf("hong: " #x "= %d\n", x);
#define PRI(x) printf("hong: " x "= %d\n", x);
#define AA(...) printf("-%d--%d-%d-\n", __VA_ARGS__);
int main()
{
	PRINT("5");
	PRI("5");
	AA(5);
	AA(5, 5);
	printf("-%d-%d-\n");

	return 0;
}