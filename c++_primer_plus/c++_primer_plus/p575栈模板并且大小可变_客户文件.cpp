#include <iostream>
#include <cstdlib>
#include <ctime>
#include "p574栈模板并且大小可变_头文件.h"
const int Num = 10;
int main()
{
	std::srand(std::time(0));
	std::cout << "Please enter stack size: ";
	int stacksize;
	std::cin >> stacksize;
	Stack<const char *> st(stacksize);

	const char * in[Num] = {
		" 1: Hank Gilgamesh", " 2: Kiki Ishtar",
		" 3: Betty Rocker", " 4: Portia Koop",
		" 5: Wolfgang Kibble", " 6: Portia Koop",
		" 7: Joy Almondo", " 8: Zaverie Paprika",
		" 9: Juan Moore", " 10: Misha Mache"
	};
	const char * out[Num];

	int process = 0;
	int nextin = 0;
	while (process < Num)
	{
		if (st.isempty())
			st.push(in[nextin++]);
		else if (st.isfull())
			st.pop(out[process++]);
		else if (std::rand() % 2 && nextin < Num)  // 50-50 chance
			st.push(in[nextin++]);
		else
			st.pop(out[process++]);
	}
	for (int i = 0; i < Num; i++)
		std::cout << out[i] << std::endl;

	std::cout << "Bye!\n";
	return 0;
}