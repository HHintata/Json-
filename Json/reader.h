#pragma once
#include<string>
#include<fstream>
class Reader
{
private:
	std::string str; //需要解析的字符串
	int len; //字符串长度
	int pos; //当前位置，下标
public:
	Reader();
	Reader(const std::string input); //从文本中读取字符串
	Reader(std::ifstream* input); //从流中读取字符串
	~Reader();
	char readChar(); //读取一个字符
	char peekChar();  //预读取一个字符
	bool isEOF(); //判断是否为最后一个字符
	void ignoreSpace(); //跳过空格符
	bool judge(std::string tmp); //检查是否能匹配tmp串
	std::string getStr();
	int getPos();
};