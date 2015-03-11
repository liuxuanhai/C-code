// ≥Ã–Ú«Âµ• 9.7
#include <iostream>
int tom = 3;           // external variable
int dick = 30;         // external variable
static int harry = 300; // static, internal linkage

// function prototype
void remote_access();

int main()
{
	using namespace std;
	cout << "main() reports the following address:\n";
	cout << &tom << " = &tom, " << &dick << " = &dick ";
	cout << &harry << " = &harry\n";
	remote_access();

	return 0;
}