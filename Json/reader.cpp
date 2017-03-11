#include "reader.h"
Reader::Reader(){}
Reader::Reader(const std::string input) :str(input), pos(0)
{
	len = input.size();
}
Reader::Reader(std::ifstream* input) : pos(0)
{
	char buf[128];
	if (input)
	{
		while (!input->eof())
		{
			input->getline(buf, 128);
			str += buf;
		}
		len = str.size();
	}
}
Reader::~Reader(){}
char Reader::readChar()
{
	if (!isEOF()) return str[++pos];
	else return 'f';
}
char Reader::peekChar() //若为最后一个字符待处理
{
	if (!isEOF()) return str[pos];
	else return 'f';
}
bool Reader::isEOF() //最后一个的话为true
{
	if (len <= pos) return true;
	return false;
}
void Reader::ignoreSpace()
{
	while (!isEOF())
	{
		if (isspace(peekChar())) readChar();
		else break;
	}
}
bool Reader::judge(std::string tmp)
{
	for (int i = 0; i < tmp.size(); i++)
	{
		if (isspace(str[pos]))
		{
			pos++; continue;
		}
		if (str[pos] != tmp[i]) return false;
		pos++;
	}
	return true;
}
std::string Reader::getStr()
{
	return str;
}
int Reader::getPos()
{
	return pos;
}