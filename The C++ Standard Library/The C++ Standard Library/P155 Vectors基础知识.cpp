			// 注意, vector的迭代器是由实作版本决定的, 也许并不是一个一般的指针

// 1.	vector 矢量		模塑出一个动态数组, 抽象概念: "将元素置于动态数组中加以管理"	PS: C++Standard并未要求必须以动态数组实现vector, 只是规定了相应条件和操作复杂度
// 2.	vector的元素可以是任意类别的T, 但是必须具备assignable和copyable两个性质
// 3.	Vectors的能力:
		// 1.	vectors将元素复制到内部的dynamic array中, 元素之间总是存在某种顺序, 是有序集(ordered collection)
		// 2.	支持随机存取(常数时间), vector的迭代器是随机存取迭代器, 所以对任何一个STL算法都奏效
		// 3.	在末端添加或删除元素时, vector的性能相当好, 前端或中部就不怎么样了
// 4.	大小(Size)和容量(Capacity)
		// 1.	操作大小的函数	
			// 1.	size()		返回容器中的元素数量
			// 2.	empty()		判断容器是否为空(相当于size() == 0, 但可能更快)
			// 3.	max_size()	返回元素的最大可能数量
			// 4.	capacity()	返回vector实际能容纳的元素数量, 如果超过这个数量, vector就有必要重新配置内部存储器
		// 2.	vector的容量很重要
			// 1.	一旦内存重新配置, 和vector元素相关的所有references, pointers, iterators都会失效
			// 2.	内存重新分配很耗时间	所以如果vector管理了references, pointers, iterators或者执行速度很重要, 就必须考虑兼容性问题
			// 3.	提前保留适当容量, 避免一再重新配置内存:
				// 1.	std::vector<int> v;	v.reserve(80);	reserve(储备, 保留, 预留) 创建一个空vector然后预留出80个元素的空间大小 预留内存不能主动被使用!
				// 2.	std::vector<T> v(5);	创建一个vector然后用5个values初始化它, 调用T类型的构造函数5次, 当然, 要获得这种能力, 此种元素必须提供一个default构造函数, 当然, 这很耗时, 如果只是为了保留足够内村, 倒不如使用reserve()	 PS: 注意, 如果T是int等基本型别, 他的构造函数将把基本型别初始化为零, 如: int i1; int i2 = int();
				// 3.	Vectors的容量概念上和strings类似, 不过有一个不同点, vector不能使用reserve()来缩减容量, 如果调用reserve()所给的参数比当前vector的容量还小, 不会引发任何反应
				// 4.	std::vector<int> v; 分配一个空vector, 但是当第一次安插元素时会一口气配置整块内存(例如2k, 根据实现????不是用reserve()自己分的??????), 所以, 如果你有一大堆vectors, 每个Vectors实际元素却寥寥无几, 那么浪费的内存将会非常可观
				// 5.	因为vectors的容量不会缩减, 所以即使删除元素, 其references, pointers, interator也会继续有效, 然而安插操作却可能使references, pointer, iterators失效(因为安插可能导致vector重新配置内存空间)
		// 3.	间接缩减vector容量的小窍门
			// 1.	两个vectors交换容量后, 两者的容量也会互换
				// 1.	template<class T>
				//		void shrinkCapacity(std::vector<T> & v)
				//		{ std::vector<T> temp(v);	// copy elements into a new vector // 构造临时temp拷贝v的时候只拷贝元素, 容量和地址都变了
				//		  v.swap(temp);}			// swap internal vector data	internal 内部的		// 再把temp跟v对换, 实际让他们的堆指针互相对调了
				// 2.	上边使得references, pointers, iterators都失效了
			// 2.	甚至可以直接这样缩减
				// 1.	std::vector<T>(v).swap(v);	// 将上边的两步放在了一个语句中
// 5.	Vector的操作函数
	// 1.	构造, 析构
		// 1.	vector<Elem> c;			// 产生一个空vector, 里面没有任何元素, 没有任何容量
		// 2.	vector<Elem> c1(c2);	// 产生同类型vector的副本(所有元素都被拷贝, 容量不拷贝, 地址不一样)
		// 3.	vector<Elem> c(n);		// 利用元素的default构造函数生成一个大小为n的vector, 基本类型如int()生成0
		// 4.	vector<Elem> c(n, elem)	// 产生一个大小为n的vector, 每一个元素都是elem
		// 5.	vector<Elem> c(beg, end)// 产生一个vector 以区间[beg, end]作为元素初值
		// 6.	c.~vector<Elem>()		// 销毁所有元素, 并释放内存
	// 2.	非变动性操作函数
		// c.size() c.empty() c.max_size() capacity() reserve() c1 == c2  c1 != c2  c1 < c2  c1 > c2  c1 <= c2  c1 >= c2
		// PS: reserve()的确会更易变动(modify)vector, 因为他造成所有references, pointers和iterators失效, 但是, 从逻辑来说, 容器并没有发生变化, 所以还是把它列在这里
	// 3.	赋值操作
		// 1.	c1 = c2 将c2的全部元素赋值给c1, 预留容量不复制, 地址不一
		// 2.	c.assign(n, elem)	复制n个elem, 赋值给c, c多出n的元素会被设置成保留容量
		// 3.	c.assign(beg, end)	将区间[beg, end)内的元素赋值给c, 其中beg, end指的是迭代器
		// 4.	c1.swap(c2)			将c1和c2元素互换, 内部指向堆的指针对换, 所以保留容量, 地址都换了过去并保持不变
		// 5.	swap(c1, c2);		同上, 此为全局函数
	// 4.	元素存取
		// 1.	c.at(idx)	返回idx所标示的元素, 如果idx越界, 抛出out_of_range
		// 2.	c[idx]		返回idx所标示的元素, !不进行范围检查
		// 3.	c.front()	返回第一个元素, !不检查第一个元素是否存在
		// 4.	c.back()	返回最后一个元素, !不检查最后一个元素是否存在
	// 5.	迭代器相关函数  PS: vector迭代器是random access iterators(随机存取迭代器), 理论上讲可以通过这个迭代器操作所有STL算法
				// 迭代器的确切型别由实作版本决定, 对于Vectors, 通常就是一般指针, 一般指针就是随机存取迭代器	
				// 迭代器持续有效, 除非发生以下两种情况:	1. 使用者在较小索引位置安插或移除元素 2. 由于容量变化而引起的内存重新分配
		// 1.	c.begin()	返回一个随机存取迭代器, 指向第一个元素
		// 2.	c.end()		返回一个随机存取迭代器, 指向最后元素的 !下一个位置
		// 3.	c.rbegin()	返回一个逆向迭代器, 指向逆向迭代器的第一个元素
		// 4.	c.rend()	返回一个逆向迭代器, 指向逆向迭代器的最后元素的下一个位置
	// 6.	vector的安插, 移除相关操作
		// 1.	c.insert(pos, elem)		在pos位置上插入一个elem副本, 并返回新元素位置
		// 2.	c.insert(pos, n, elem)	在pos位置上插入n个elem副本, 无回传值
		// 3.	c.insert(pos, beg, end) 在pos位置上插入区间[beg, end]内的所有元素的副本, 无传回值
		// 4.	c.push_back(elem)		在尾部添加一个elem副本
		// 5.	c.pop_back()			移除最后一个元素, 但不回传
		// 6.	c.erase(pos)			移除pos位置上的元素, 返回下一个元素的位置, 即有可能返回的是pos, 因为后一个元素替补到前面去了
		// 7.	c.erase(beg, end)		移除[beg, end)区间内的所有元素, 返回下一个元素的位置
		// 8.	c.resize(num)			将元素数量改为num(如果size()变大了, 多出来的元素都需要以default构造函数构造完成)
		// 9.	c.resize(num, elem)		将元素数量改为num(如果size()变大了, 多出来的元素都是elem的副本)
		// 10.	c.clear()				移除所有元素, 将容器清空
// 6.	异常处理(Exceptional Handling): 不做详细解释, 书中P156

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
bool jiangxu(int &, int &);
int main()
{
	int i0 = int();	// 基本型别的 "不含参数的, 明确的构造函数调用" , 基本型别初始化为0
		// 这可以保证撰写template程序代码的时候, 任何型别都有一个确切的初值
		// 这里显示调用default构造函数进行初始化时可以的

	// 这里隐式调用基本型别的default构造函数是不可以的
	// int i1(); error LNK2019: 无法解析的外部符号 "int __cdecl i1(void)" (?i1@@YAHXZ)，该符号在函数 _main 中被引用
	std::cout << "基本型别默认构造初始化i0 = " << i0 << std::endl;

	// 构造, 析构
	std::vector<int> c;	// 产生一个空vector, 其中没有任何元素
	//std::cout << c[0];	// 弹出运行期间的warning, 提示越界
	//std::cout << c.at(0);	// 抛出异常, 运行期间abort()
	std::cout << "c的容量是: " << c.capacity() << std::endl;
	std::cout << "c的最大可能数量是: " << c.max_size() << std::endl << std::endl;
	std::vector<int> c1(1);	// 初始化一个元素会导致多分配内存吗? 不会
	std::cout << "c1[0] = " << c1[0] << std::endl;	// 显示调用基本类型的构造函数int(), 初始化为0
	//std::cout << c1[1];	// 弹出运行期间的warning, 提示越界
	//std::cout << c1.at(1);	// 抛出异常, 运行期间abort()
	std::cout << "c1的容量是: " << c1.capacity() << std::endl << std::endl;
	
	std::vector<int> c2(1);
	c2.reserve(20);	// 增大容量 成功
	std::cout << "c2的元素数量是: " << c2.size() << "   c2的容量是: " << c2.capacity() << "    地址是: " << (void *)&(c2[0]) << std::endl;
	c2.reserve(10);	// reserve() 缩小容量 失败
	std::cout << "c2的元素数量是: " << c2.size() << "   c2的容量是: " << c2.capacity() << "    地址是: " << (void *)&(c2[0]) << std::endl << std::endl;

	std::cout << "c1的元素数量是: " << c1.size() << "   c1的容量是: " << c1.capacity() << "    地址是: " << (void *)&(c1[0]) << std::endl;
	c2.swap(c1);	// 交换缩小容量 成功	// 交换后c2指向了c1的堆位置, c1指向了c2的堆位置
	std::cout << "c2的元素数量是: " << c2.size() << "   c2的容量是: " << c2.capacity() << "    地址是: " << (void *)&(c2[0]) << std::endl;
	std::cout << "c1的元素数量是: " << c1.size() << "   c1的容量是: " << c1.capacity() << "    地址是: " << (void *)&(c1[0]) << std::endl << std::endl;

	c2.reserve(5);	// 多分出来的那部分是未初始化的
	std::cout << "c2的最大可能数量是: " << c2.max_size() << std::endl;
	std::cout << "c2的元素数量是: " << c2.size() << "   c2的容量是: " << c2.capacity() << "    地址是: " << (void *)&(c2[0]) << std::endl << std::endl;

	std::vector<int> c3(3);	// 所有的三个元素初始化为int()即0
	c3.reserve(20);
	c3.at(2) = 2;	// 初始化给定的内存是程序员可以主动的随便用的
	//c3.at(4) = 4;	// 预留的内存是为了自动增大的时候省的重新分配内存, 程序员自己能随便使用的只有初始化时指定的内存大小
	//std::cout << c3.at(1);不能使用未初始化的
	std::cout << c3.at(2) << std::endl;
	std::cout << "c3的元素数量是: " << c3.size() << "   c3的容量是: " << c3.capacity() << "    地址是: " << (void *)&(c3[0]) << std::endl << std::endl;
	c3.swap(c3);	// 这样的交换不能实现缩小容量
	std::cout << "c3的元素数量是: " << c3.size() << "   c3的容量是: " << c3.capacity() << "    地址是: " << (void *)&(c3[0]) << std::endl << std::endl;
	std::vector<int>(c3).swap(c3);	// 这样的交换才能缩小容量	生成一个临时变量, 拷贝了c3的内容然后与c3交换   实际上是临时变量生成拷贝的时候把容量缩小了, 但是, 整个语句执行完以后, !!!!c3的地址也发生了改变!!!
	std::cout << "c3的元素数量是: " << c3.size() << "   c3的容量是: " << c3.capacity() << "    地址是: " << (void *)&(c3[0]) << std::endl << std::endl;

	std::vector<int> c4(c2);	// 初始化的时候的拷贝是c4只拷贝c2的元素, 容量和地址都不一样
	std::cout << "c4的元素数量是: " << c4.size() << "   c4的容量是: " << c4.capacity() << "    地址是: " << (void *)&(c4[0]) << std::endl << std::endl;

	std::vector<int> c5(5, 6);
	std::cout << "c5中的所有元素都被初始化为: " << std::endl;
	for (std::vector<int>::iterator i = c5.begin(); i < c5.end(); i++)
		std::cout << *i << " ";
	std::cout << std::endl;
	std::cout << "c5的元素数量是: " << c5.size() << "   c5的容量是: " << c5.capacity() << "    地址是: " << (void *)&(c5[0]) << std::endl << std::endl;

	//std::vector<int> c6(); 构造函数中的范围赋值>>>>>>>???????????????????????????
	std::vector<int> c7;
	c5.reserve(10);
	std::cout << "c5的元素数量是: " << c5.size() << "   c5的容量是: " << c5.capacity() << "    地址是: " << (void *)&(c5[0]) << std::endl;
	c7 = c5;
	std::cout << "c7的元素数量是: " << c7.size() << "   c7的容量是: " << c7.capacity() << "    地址是: " << (void *)&(c7[0]) << std::endl;
	for (std::vector<int>::iterator i = c7.begin(); i != c7.end(); i++)
		std::cout << *i << " ";
	std::cout << std::endl;
	c7.assign(3, 4);
	for (std::vector<int>::iterator i = c7.begin(); i != c7.end(); i++)
		std::cout << *i << " ";
	std::cout << std::endl;
	std::cout << "c7的元素数量是: " << c7.size() << "   c7的容量是: " << c7.capacity() << "    地址是: " << (void *)&(c7[0]) << std::endl;
	std::vector<int> c8(10);
	std::cout << "c8的内容: ";
	int j = 0;
	for (std::vector<int>::iterator i = c8.begin(); i != c8.end(); ++i, ++j)
	{
		*i = j;
		std::cout << *i << " ";
	}
	std::cout << std::endl;
	c7.assign(c8.begin(), c8.end());	// [beg, end)
	std::cout << "c7.assign(c8.begin(), c8.end());之后的c7内容: ";
	for (std::vector<int>::iterator i = c7.begin(); i != c7.end(); i++)
		std::cout << *i << " ";
	std::cout << std::endl;
	std::cout << "c7.front() = " << c7.front() << std::endl;
	std::cout << "c7.back() = " << c7.back() << std::endl << std::endl;

	std::vector<int> c9;
	// std::cout << c9.front(); 运行出错, 说引用时无效的    !!!!书上说的发生越界会出现未定义行为

	std::vector<int> c10(4);
	c10.reserve(20);
	j = 0;
	std::cout << "c10的内容是: \n";
	for (std::vector<int>::iterator i = c10.begin(); i != c10.end(); ++i, ++j)
	{
		*i = j;
		std::cout << &(*i) << "地址下的: " << *i << " \n";
	}
	std::cout << std::endl;
	std::cout << *c10.erase(c10.begin()) << std::endl;	// 把迭代器c10.begin()位置 上 的元素移除了, 然后观察地址可以看到后边的元素补在了前面空缺的位置
		// erase返回了pos后一个元素的迭代器 由于后一个元素替补上了移除元素的位置, 所以返回的还是pos的位置, 即返回旧的c10.begin(), 新的c10.begin()==旧的
		// 当然 如果把上边的额begin改成end就出错了, RUNTIMEERROR: 未定义的行为

	std::cout << "c10.erase(c10.begin()): \n";
	for (std::vector<int>::iterator i = c10.begin(); i != c10.end(); ++i)
		std::cout << &(*i) << "地址下的: " << *i << " \n";
	std::cout << *c10.insert(c10.begin(), 0) << std::endl;
	std::cout << "c10.insert(c10.begin(): \n";
	for (std::vector<int>::iterator i = c10.begin(); i != c10.end(); ++i)
		std::cout << &(*i) << "地址下的: " << *i << " \n";
	std::vector<int>temp(c10.begin(), c10.begin() + 3);	// 保存c10中要移除的部分
	std::cout << *c10.erase(c10.begin(), c10.begin() + 3) << std::endl;	// 把[beg, end)移除了
	std::cout << "c10.erase(c10.begin(), c10.begin() + 3)\n";
	for (std::vector<int>::iterator i = c10.begin(); i != c10.end(); ++i)
		std::cout << &(*i) << "地址下的: " << *i << " \n";
	std::cout << *c10.insert(c10.begin(), 3, -1);	// 说是没有返回值, 实际测试返回了第一个新元素的位置std::cout << &(*c10.insert(c10.begin(), 3, -1));
	std::cout << "c10.insert(c10.begin(), 3, -1):\n";
	for (std::vector<int>::iterator i = c10.begin(); i != c10.end(); ++i)
		std::cout << &(*i) << "地址下的: " << *i << " \n";
	std::cout << *c10.insert(c10.begin(), temp.begin(), temp.end()) << std::endl;	// 说是[beg, end]但是实际测试是[beg, end)
	std::cout << "c10.insert(c10.begin(), temp.begin(), temp.end()):\n";
	for (std::vector<int>::iterator i = c10.begin(); i != c10.end(); ++i)
		std::cout << &(*i) << "地址下的: " << *i << " \n";
	
	std::cout << "利用pop_back()删除c10所有的元素: \n";
	j = (int)c10.size();	// 因为pop_back()的同时, c10.size()是不断变化的, 所以不能直接放在for循环中的j的位置
	for (int i = 0; i < j; i++)
		c10.pop_back();
	for (std::vector<int>::iterator i = c10.begin(); i != c10.end(); ++i)
		std::cout << &(*i) << "地址下的: " << *i << " \n";
	std::cout << "c10中没有元素了\n";

	std::cout << "利用c10.resize(5)将size()变大: \n";	// 变大的部分由元素的default构造函数完成
	c10.resize(5);
	for (std::vector<int>::iterator i = c10.begin(); i != c10.end(); ++i)
		std::cout << &(*i) << "地址下的: " << *i << " \n";
	std::cout << "利用c10.resize(10, 1)将size()变大: \n";	// 变大的部分由1的副本完成
	c10.resize(10, 1);
	for (std::vector<int>::iterator i = c10.begin(); i != c10.end(); ++i)
		std::cout << &(*i) << "地址下的: " << *i << " \n";
	std::cout << "利用c10.clear()清空元素: \n";
	c10.clear();
	for (std::vector<int>::iterator i = c10.begin(); i != c10.end(); ++i)
		std::cout << &(*i) << "地址下的: " << *i << " \n";
	std::cout << "c10中没有元素了\n";

	std::vector<int> c11;
	for (int i = 0; i < 6; i++)
	{
		c11.insert(c11.begin(), i);
		c11.push_back(i);
	}
	std::vector<int> c12(c11);
	std::cout << "\nc11中的所有元素如下: \n";
	for (std::vector<int>::iterator i = c11.begin(); i != c11.end(); ++i)
		std::cout << *i << " ";
	std::cout << std::endl;

		// algorithm 中的remove(beg, end, elem)算法删除容器中的 !所有! 与elem相等的数据项
		// algorithm 中的find(beg, end, elem)寻找到容器中第一个与elem相等的位置, 配合vector<T>::earse()可以实现删除第一个的效果
		// algorithm 中的diatance(beg, end)返回两个迭代器之间的距离

	std::cout << "利用算法把c11的所有value == 3的元素删除: \n";
	remove(c11.begin(), c11.end(), 3);	// 元素3被覆盖了, 但是最后的4 5 两个元素没有元素覆盖他们
		// 实际上remove()并没有改变群集中的元素数量, 但是从逻辑上讲, 4 5已经不属于这个群集了
		// 还好, 这个算法返回了一个新的终点(最后一个元素的后一个位置), 可以利用该终点获得新的区间, 缩减后容器的大小, 或是被删除元素的个数
		// remove不调用erase直接删除两个多余的 4 5 是STL为了获取灵活性而付出的代价, STL将数据和算法分离开来, 然而, 迭代器只是"容器中的某一位置"的抽象概念, 所以, 迭代器对自己所属的容器一无所知, 所以, end后边的元素属于谁他也不知道, 不能随便往前放(如果知道这个容器的erase()就行了, 但是他不知道), 也正是因为这样, 任何"以迭代器访问容器元素"的算法都不得(无法)透过迭代器嗲用容器类别提供的任何成员函数(这里是erase()), 这样设计的一个重要结果是: 算法的操作对象不一定是"容器内的全部元素"所形成的区间, 而可以是那些元素的子集, 甚至算法可以运作于一个"并未提供成员函数erase()"的容器(array就是一个例子), 所以, 为了达成算法的最大弹性, 不要求"迭代器必须了解其容器的细节"还是很有道理的...

	for (std::vector<int>::iterator i = c11.begin(); i != c11.end(); ++i)
		std::cout << *i << " ";

	std::cout << "\nremove算法的改进版本:\n";
	std::cout << "c12中的所有元素如下: \n";
	for (std::vector<int>::iterator i = c12.begin(); i != c12.end(); ++i)
		std::cout << *i << " ";
	std::cout << std::endl;
	std::vector<int>::iterator end = remove(c12.begin(), c12.end(), 3);	// remove返回新的终点
	std::cout << "被删除了 " << distance(end, c12.end()) << " 个元素\n";
	c12.erase(end, c12.end());
	for (std::vector<int>::iterator i = c12.begin(); i != c12.end(); ++i)
		std::cout << *i << " ";
	std::cout << "\n只是移除c12中的第一个4: \n";
	std::vector<int>::iterator pos;
	pos = find(c12.begin(), c12.end(), 4);	// 如果没有找到的话返回的是end的值
	if (pos != c12.end())	// 如果找到了就擦除
		c12.erase(pos);
	for (std::vector<int>::iterator i = c12.begin(); i != c12.end(); ++i)
		std::cout << *i << " ";
	std::cout << std::endl;

	// algorithm 中的 fill(beg, end, elem) 实现用一个特定的值组装一个容器
	std::cout << "algorithm 中的 fill 实现用一个特定的值组装一个容器: \n";
	std::fill(c12.begin(), c12.end(), 9);
	for (std::vector<int>::const_iterator i = c12.begin(); i != c12.end(); i++)
		std::cout << *i << " ";
	std::cout << std::endl;

	// algorithm 中的 copy(c1.beg, c1.end, c2.beg) 实现将一个容器类的值复制到另一个(或同一个, 只要区间不重叠)容器类
	std::cout << "algorithm 中的 copy 作用与c13: \n";
	std::vector<int> c13;
	std::cout << "c13的内容如下: \n";
	for (int i = 0; i < 10; ++i)
	{
		c13.push_back(i);
		std::cout << c13.at(i) << " ";
	}
	std::cout << "\ncopy以后的结果如下:\n";
	std::copy(c13.begin(), c13.begin() + 4, c13.end() - 4);
	for (std::vector<int>::const_iterator i = c13.begin(); i != c13.end(); ++i)
		std::cout << *i << " ";
	std::cout << "\n";

	// algorithm 中的 sort() 以升序排列容器中的项
	std::cout << "std::sort(c13.begin(), c13.end()):\n";
	std::sort(c13.begin(), c13.end());
	for (std::vector<int>::const_iterator i = c13.begin(); i != c13.end(); ++i)
		std::cout << *i << " ";
	// 改为降序
	std::cout << "\nstd::sort(c13.begin(), c13.end(), jiangxu): \n";
	std::sort(c13.begin(), c13.end(), jiangxu);
	for (std::vector<int>::const_iterator i = c13.begin(); i != c13.end(); ++i)
		std::cout << *i << " ";

	// string
	std::string str;
}

bool jiangxu(int & i1, int & i2)
{
	return i1 > i2;
}