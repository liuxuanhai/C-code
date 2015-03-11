// ≥Ã–Ú«Âµ• 9.8
#include <iostream>
extern int tom;      // tom defined elsewhere
static int dick = 10;// overrides external dick
int harry = 200;     // external variable definition
					// no conflict with twofile1 harry

void remote_access()
{
	using namespace std;
	cout << "remote_access() reports the following addresses:\n";
	cout << "main() reports the following address:\n";
	cout << &tom << " = &tom, " << &dick << " = &dick ";
	cout << &harry << " = &harry\n";
}