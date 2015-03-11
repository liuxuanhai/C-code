#include <iostream>
#include <string>
#include <vector>
#include <algorithm>  // sort(), find()

struct Review
{
	std::string title;
	int rating;
};

bool operator<(const Review & r1, const Review & r2);
bool worseThan(const Review & r1, const Review & r2);
bool FillReview(Review & rr);
void ShowReview(const Review & rr);

int main(void)
{
	using namespace std;

	vector<Review> books;
	Review temp;
	while (FillReview(temp))
		books.push_back(temp);
	if (books.size() > 0)
	{
		cout << "Thank you. You entered the following "
			<< books.size() << " ratings:\n"
			<< "Rating\tBook\n";
		for_each(books.begin(), books.end(), ShowReview);

		sort(books.begin(), books.end());  // 默认使用的是<, 按从小到大的顺序排列
		cout << "Sorted by title: \nRating\tBook\n";
		for (Review x: books)  // 基于范围的for循环是为用于STL而设计的
			ShowReview(x);
		// 不同于for_each(), 基于范围的for循环可以修改容器的内容, 诀窍是制定一个引用参数
		//for (Review & x: books) 
		//{
			//x.rating = 0; 
			//ShowReview(x);
		//}
		// 如果不加上引用符号将会对for中的临时变量x进行赋值


		sort(books.begin(), books.end(), worseThan);
		cout << "Sorted by rating:\nRating\tBook\n";
		for (auto x: books) ShowReview(x);  // 当然, 使用auto更方便

		random_shuffle(books.begin(), books.end());
		cout << "After shuffling:\nRating\tBook\n";
		for_each(books.begin(), books.end(), ShowReview);
	}
	else
		cout << "No entries.";
	cout << "Bye.\n";

	return 0;
}

// 如果容器元素是用户定义的对象, 则要使用sort(), 必须定义能够处理该类对象的operator<()函数
// 由于Review是一个结构, 因此其成员是公有的, 这样的非成员函数将为:
bool operator<(const Review & r1, const Review & r2)
{
	if (r1.title < r2.title)
		return true;
	else if (r1.title == r2.title && r1.rating < r2.rating)
		return true;
	else
		return false;
}

bool worseThan(const Review & r1, const Review & r2)
{
	if (r1.rating < r2.rating)
		return true;
	else
		return false;
}

bool FillReview(Review & rr)
{
	std::cout << "Enter book title (quit to quit): ";
	std::getline(std::cin, rr.title);
	if (rr.title == "quit")
		return false;
	std::cout << "Enter book rating: ";
	std::cin >> rr.rating;
	if (!std::cin)
		return false;
	while (std::cin.get() != '\n');
	return true;
}

void ShowReview(const Review & rr)
{
	std::cout << rr.rating << "\t" << rr.title << std::endl;
}