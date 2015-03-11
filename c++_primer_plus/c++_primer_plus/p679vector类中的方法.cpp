// size(), begin(), end(), push_back(), erase(), insert()
#include <iostream>
#include <string>
#include <vector>

struct Review
{
	std::string title;
	int rating;
};

bool FillReview(Review & rr);
void ShowReview(const Review & rr);

int main(void)
{
	using std::cout;
	using std::vector;

	vector<Review> books;
	Review temp;
	while (FillReview(temp))
		books.push_back(temp);  // 将temp中的内容添加到books的末尾
	int num = books.size();  // 返回books中的元素个数
	if (num > 0)
	{
		cout << "Thank you. You entered the following:\n"
			<< "Rating\tBook\n";
		for (int i = 0; i < num; i++)
			ShowReview(books[i]);
		cout << "Reprising:\nRating\tBook\n";
		vector<Review>::iterator pr;  // vector 中的迭代器类型为iterator
		for (pr = books.begin(); pr != books.end(); pr++)
			ShowReview(*pr);
		vector<Review> oldlist(books);  // 复制构造函数
		if (num > 3)
		{
			// remove 2 items
			books.erase(books.begin() + 1, books.begin() + 3); // [1, 3)被删除
			cout << "After erasure:\n";
			for (pr = books.begin(); pr != books.end(); pr++)
				ShowReview(*pr);
			// insert 1 item
			books.insert(books.begin(), oldlist.begin() + 1, oldlist.begin() + 2);  // 在books.begin()前面加上了[1, 2)
			cout << "After insertion:\n";
			for (pr = books.begin(); pr != books.end(); pr++)
				ShowReview(*pr);
		}
		books.swap(oldlist);  // books中的内容变成了oldlist的, 他们交换了
		cout << "Swapping oldlist with books:\n";
		for (pr = books.begin(); pr != books.end(); pr++)
			ShowReview(*pr);
	}
	else
		cout << "Nothing entered, nothing gained.\n";

	return 0;
}

bool FillReview(Review & rr)
{
	std::cout << "Enter book title (quit to quit): ";
	std::getline(std::cin, rr.title);
	if (rr.title == "quit")  // 因为title是一个string对象, 它重载了==所以可以直接这么进行比较了
		return false;
	std::cout << "Enter book rating: ";
	std::cin >> rr.rating;
	if (!std::cin)
		return false;
	while (std::cin.get() != '\n')
		continue;
	return true;
}

void ShowReview(const Review & rr)
{
	std::cout << rr.rating << "\t" << rr.title << std::endl;
}