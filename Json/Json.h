//#pragma once
#include "reader.h"
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <iostream>
enum Jsontype    //������������
{
	Json_number,  //����
	Json_bool,   //����ֵ
	Json_string,   //�ַ���
	Json_dict,  //�ֵ�
	Json_list, //��
	Json_null,  //NULL
};
class JsonList;
class JsonDict;
class JsonValue
{
	friend class Json;
private:
	Jsontype type;    //����������Ϣ
public:
	JsonValue(Jsontype tmp);   //���캯��
	Jsontype getType();   //�������
	JsonValue();
	virtual std::string toStr();   //תΪ������ַ���
	virtual JsonList* toList();       //תΪ������
	virtual JsonDict* toDict();   //תΪ�ֵ�����
	virtual std::string getStr();  //תΪ�洢���ַ���
};

class JsonString :public JsonValue
{
private:
	std::string str;   //�ַ���ֵ
public:
	JsonString(std::string tmp);  //���캯��
	std::string toStr();  //ͬ��
	std::string getStr();
};
class JsonDict :public JsonValue
{
private:
	std::vector<std::string>dict_key;   //����keyֵ
	std::unordered_map<std::string, JsonValue*> _map;  //����key��value��ӳ��
public:
	void append(std::string key, JsonValue* value);  //��Ӽ�ֵ��
	JsonDict* toDict();   //תΪ�ֵ�����
	std::string toStr();  //ͬ��
	std::string getStr();
	JsonValue* getValue(int index);  //���������ֵ
	JsonValue* getValue(std::string key);  //�Լ����ֵ
	void clear();  
	int getSize(); //��ü�ֵ�Ը���
	JsonDict();
	~JsonDict();
};
class JsonList :public JsonValue
{
private:
	std::vector<JsonValue*>list;  //�洢��
public:
	void append(JsonValue* tmp);  //��ӱ�Ԫ��
	JsonValue* getValue(int index); //��������ñ�Ԫ��
	void clear();
	JsonList* toList();  //ͬ��
	std::string toStr();
	std::string getStr();
	JsonList();
	~JsonList();
};
class JsonBool :public JsonValue
{
private:
	bool Bool;
public:
	JsonBool(bool tmp);  
	std::string toStr();
	std::string getStr();
	~JsonBool();
};
class JsonNumber :public JsonValue
{
private:
	double number;
public:
	JsonNumber(double tmp);
	std::string toStr();
	std::string getStr();
};
class JsonNull :public JsonValue
{
private:
	int flag;
public:
	JsonNull();
	std::string toStr();
	std::string getStr();
};
class Json
{
private:
	JsonValue* root; //Json����ĸ���ַ
	JsonValue* parseValue(Reader& Context);    //����һ��Json����
	JsonValue* parseNumber(Reader& Context);  //����һ������
	JsonString* parseString(Reader& Context);  //����һ���ַ���
	JsonList* parseList(Reader& Context);    //����һ����
	JsonDict* parseDict(Reader& Context);  //����һ���ֵ�
	JsonBool* parseBool(Reader& Context); //����һ������ֵ
	JsonNull* parseNull(Reader& Context); //����NULL
public:
	JsonValue* getRoot();
	std::string ToStr();  //תΪ���ʱ���ַ���
	std::string getStr();  //תΪ�洢���̵��ַ���
	Json(const std::string input);  //���ı�����
	Json(std::ifstream* input);  //��������
	~Json();
};