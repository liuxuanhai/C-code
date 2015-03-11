// 自己总结
// 基于范围的for循环简化了一种常见的循环任务: 对数组(或容器类, 如vector和array)的每个元素执行了相同的操作
#include <iostream>
int main()
{
	double prices[5] = {4.99, 10.99, 6.87, 7.99, 8.49};
	// 显示数据
	for (double x : prices)
		std::cout << x << std::endl;
	// 更改数据
	for (double &x : prices) // &x表示x是个引用 变量, 这种声明让接下来的代码能够修改数组的内容
	{	
		x = x * 0.80;
		std::cout << x << std::endl; // 这里为什么还是x而不是&x或其他的什么?????
	}
	// 初始化列表 // 貌似还不支持???????
	//for (int x : {3, 5, 2, 8, 6})
	//	std::cout << x << " ";
	//std::cout << std::endl;
	return 0;
}