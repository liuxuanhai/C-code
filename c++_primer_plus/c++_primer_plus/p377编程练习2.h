// 编程练习 10.10 头文件
#include <string>
using std::string;
class Person
{
private:
	static const int LIMIT = 25;
	string lname;
	char fname[LIMIT];
public:
	Person(){lname = ""; fname[0] = '\0';}  // # 1
	Person(const string & ln, const char * fn = "Heyyou");  // # 2
// the follow methods display lname and fname
	void Show() const;  // first name last name format
	void FormalShow() const;  // lastname, first name format
};