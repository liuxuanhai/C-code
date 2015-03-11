// Build: 2014-10-10 11:20:36
#ifndef HEABUTILITY_H
#define HEABUTILITY_H

#include <string>
using namespace std;

// =========== ×Ö·û´®´¦Àí ===========

class HString
{
private:
	string source;
	string curString;
	string flagStr;
public:
	HString(string source, string flagStr);
	string subStr();
	bool isEnd();
	void reset(string source, string flagStr);
};

// ==================================

#endif