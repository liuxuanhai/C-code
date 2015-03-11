#include <ctime>
#define CLOCKSTART	clock_t start =	clock()
#define CLOCKINI	start = 0
#define SHOWTIME	std::cout << "所用时间: " << clock() - start << " 毫秒" << endl