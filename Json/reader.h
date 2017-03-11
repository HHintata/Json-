#pragma once
#include<string>
#include<fstream>
class Reader
{
private:
	std::string str; //��Ҫ�������ַ���
	int len; //�ַ�������
	int pos; //��ǰλ�ã��±�
public:
	Reader();
	Reader(const std::string input); //���ı��ж�ȡ�ַ���
	Reader(std::ifstream* input); //�����ж�ȡ�ַ���
	~Reader();
	char readChar(); //��ȡһ���ַ�
	char peekChar();  //Ԥ��ȡһ���ַ�
	bool isEOF(); //�ж��Ƿ�Ϊ���һ���ַ�
	void ignoreSpace(); //�����ո��
	bool judge(std::string tmp); //����Ƿ���ƥ��tmp��
	std::string getStr();
	int getPos();
};