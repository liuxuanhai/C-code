// 练习2.3-6 利用二分查找将插入排序的时间复杂度由 n^2 改成 nlgN ?
// 1. 如果是数组存储的数据的话那么这种优化不能实现, 因为即使查找的时间由n优化成了lgn但是数组中移动位置还是需要n的时间, 这样反而增加了时间
// 2. 如果是链表存储的话这种优化是可以实现的;
#include <iostream>
using namespace std;

void binaryInsertionSort(int A[])
{

}