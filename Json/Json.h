//#pragma once
#include "reader.h"
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <iostream>
enum Jsontype    //定义数据类型
{
	Json_number,  //数字
	Json_bool,   //布尔值
	Json_string,   //字符串
	Json_dict,  //字典
	Json_list, //表
	Json_null,  //NULL
};
class JsonList;
class JsonDict;
class JsonValue
{
	friend class Json;
private:
	Jsontype type;    //保存类型信息
public:
	JsonValue(Jsontype tmp);   //构造函数
	Jsontype getType();   //获得类型
	JsonValue();
	virtual std::string toStr();   //转为输出的字符串
	virtual JsonList* toList();       //转为表类型
	virtual JsonDict* toDict();   //转为字典类型
	virtual std::string getStr();  //转为存储的字符串
};

class JsonString :public JsonValue
{
private:
	std::string str;   //字符串值
public:
	JsonString(std::string tmp);  //构造函数
	std::string toStr();  //同上
	std::string getStr();
};
class JsonDict :public JsonValue
{
private:
	std::vector<std::string>dict_key;   //保存key值
	std::unordered_map<std::string, JsonValue*> _map;  //保存key到value的映射
public:
	void append(std::string key, JsonValue* value);  //添加键值对
	JsonDict* toDict();   //转为字典类型
	std::string toStr();  //同上
	std::string getStr();
	JsonValue* getValue(int index);  //以索引获得值
	JsonValue* getValue(std::string key);  //以键获得值
	void clear();  
	int getSize(); //获得键值对个数
	JsonDict();
	~JsonDict();
};
class JsonList :public JsonValue
{
private:
	std::vector<JsonValue*>list;  //存储表
public:
	void append(JsonValue* tmp);  //添加表元素
	JsonValue* getValue(int index); //以索引获得表元素
	void clear();
	JsonList* toList();  //同上
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
	JsonValue* root; //Json对象的根地址
	JsonValue* parseValue(Reader& Context);    //解析一个Json对象
	JsonValue* parseNumber(Reader& Context);  //解析一个数字
	JsonString* parseString(Reader& Context);  //解析一个字符串
	JsonList* parseList(Reader& Context);    //解析一个表
	JsonDict* parseDict(Reader& Context);  //解析一个字典
	JsonBool* parseBool(Reader& Context); //解析一个布尔值
	JsonNull* parseNull(Reader& Context); //解析NULL
public:
	JsonValue* getRoot();
	std::string ToStr();  //转为输出时的字符串
	std::string getStr();  //转为存储过程的字符串
	Json(const std::string input);  //从文本解析
	Json(std::ifstream* input);  //从流解析
	~Json();
};