// Build: 2014-10-10 11:31:22
#include "HeabUtility.h"

HString::HString(string source, string flagStr)
{
	reset(source, flagStr);
}

void HString::reset(string source, string flagStr)
{
	this->source	= source;
	this->flagStr	= flagStr;
	this->curString = source;
}

string HString::subStr()
{
	int i;
	string temp = curString.substr(0, i = curString.find(flagStr));

	// ∑¿÷π342@45@555@ø…“‘342@45@555À¿—≠ª∑
	if (i == -1)
	{
		curString = "";
	}

	curString = curString.substr(curString.find(flagStr) + 1);
	return temp;
}

bool HString::isEnd()
{
	return curString == "";
}
