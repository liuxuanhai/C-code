// 程序清单 5.6
#include <iostream>
#include <string>
int main()
{
	using namespace std;
	cout << "Enter a word: ";
	string word;
	cin >> word;

	for (int i = word.size() - 1; i >= 0; i--) // string类中的size()获得字符串的字符数包括'\0'
		cout << word[i];
	cout << "\nBye.\n";

	// ###### 另一种更好的算法 ########
	for(int i = 0, j = word.size() - 1; i < j; ++i, --j)
	{
		 char temp;
		 temp = word[j];
		 word[j] = word[i];
		 word[i] = temp;
	}
	cout << word << endl;

	return 0;
}