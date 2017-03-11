#define _CRT_SECURE_NO_DEPRECATE
#include "json.h"
JsonNumber::JsonNumber(double tmp) :JsonValue(Json_number), number(tmp){}
JsonValue::JsonValue(Jsontype tmp) : type(tmp){}
JsonString::JsonString(std::string tmp) : JsonValue(Json_string), str(tmp){}
JsonList::JsonList() : JsonValue(Json_list){}
JsonList::~JsonList()
{
	clear();
}
JsonDict::JsonDict() : JsonValue(Json_dict) {}
JsonDict::~JsonDict()
{
	clear();
}
JsonBool::JsonBool(bool tmp) : Bool(tmp), JsonValue(Json_bool){}
JsonNull::JsonNull() : flag(1), JsonValue(Json_null){}
Json::Json(const std::string input)
{
	Reader inReader(input);
	root = parseValue(inReader);
	std::cout <<input<< std::endl;
}
Json::Json(std::ifstream* input)
{
	Reader inReader(input);
	root = parseValue(inReader);
}
Json::~Json()
{
	delete root;
}
JsonValue* Json::parseValue(Reader& Context)
{
	JsonValue* tmp = NULL;
	Context.ignoreSpace();
	if (!Context.isEOF())
	{
		Context.ignoreSpace();
		char nextChar = Context.peekChar();
		if (nextChar == '{') tmp = parseDict(Context);
		else if (nextChar == '[') tmp = parseList(Context);
		else if (nextChar == '"') tmp = parseString(Context);
		else if (nextChar == 't' || nextChar == 'f') tmp = parseBool(Context);
		else if (nextChar == '-' || iswdigit(nextChar)) tmp = parseNumber(Context);
		else if (nextChar == 'n') tmp = parseNull(Context);
		else{}
	}
	return tmp;
}
JsonValue* Json::parseNumber(Reader& Context)
{
	Context.ignoreSpace();
	std::string tmp;
	while (!Context.isEOF())
	{
		Context.ignoreSpace();
		char nextChar = Context.peekChar();
		if (nextChar == '-' || nextChar == '.' || nextChar == 'E' || nextChar == 'e' || iswdigit(nextChar))
		{
			tmp += nextChar;
			Context.readChar();
		}
		else break;
	}
	return new JsonNumber(atof(tmp.c_str()));

}
JsonString* Json::parseString(Reader& Context)
{
	Context.ignoreSpace();
	std::string tmp;
	Context.readChar();
	while (!Context.isEOF())
	{
		Context.ignoreSpace();
		char nextChar = Context.peekChar();
		if (nextChar == '\\')
		{
			nextChar = Context.readChar();
			if (nextChar == '"') tmp += "\"";
			else if (nextChar == '\\') tmp += "\\";
			else if (nextChar == '/') tmp += "/";
			else if (nextChar == 'b') tmp += "\b";
			else if (nextChar == 'f') tmp += "\f";
			else if (nextChar == 'n') tmp += "\n";
			else if (nextChar == 'r') tmp += "\r";
			else if (nextChar == 't') tmp += "\t";
			else {}
		}
		else if (nextChar == '"')
		{
			Context.readChar();
			break;
		}
		else
		{
			tmp += nextChar;
			Context.readChar();
		}
	}
	return new JsonString(tmp);
}
JsonList* Json::parseList(Reader& Context)
{
	JsonList* tmp = new JsonList();
	Context.ignoreSpace();
	Context.readChar();
	while (!Context.isEOF())
	{
		Context.ignoreSpace();
		char nextChar = Context.peekChar();
		if (nextChar == ']')
		{
			Context.readChar();
			break;
		}
		JsonValue * tmpvalue = NULL;
		tmpvalue = parseValue(Context);
		tmp->append(tmpvalue);
		if(Context.peekChar()==',') Context.readChar();
	}
	return tmp;
}
JsonDict* Json::parseDict(Reader& Context)
{
	JsonDict* tmp = new JsonDict();
	Context.ignoreSpace();
	Context.readChar();
	while (!Context.isEOF())
	{
		Context.ignoreSpace();
		char nextChar = Context.peekChar();
		if (nextChar == '}')
		{
			Context.readChar();
			break;
		}
		JsonString* tmp_key = parseString(Context);
		Context.readChar();
		JsonValue* tmp_value = parseValue(Context);
		tmp->append(tmp_key->getStr(), tmp_value);
		if (Context.peekChar() == ',') Context.readChar();
	}
	return tmp;
}
JsonBool* Json::parseBool(Reader& Context)
{
	if (Context.judge("true")) return new JsonBool(true);
	else if (Context.judge("false")) return new JsonBool(false);
	else
	{
	}
	return NULL;
}
JsonNull* Json::parseNull(Reader& Context)
{
	if (Context.judge("null")) return new JsonNull();
	return NULL;
}
void JsonList::append(JsonValue* tmp)
{
	list.push_back(tmp);
}
JsonValue* JsonList::getValue(int index)
{
	return list[index];
}
void JsonDict::append(std::string key, JsonValue* value)
{
	_map[key] = value;
	dict_key.push_back(key);
}
JsonValue* JsonDict::getValue(int index)
{
	return _map[dict_key[index]];
}
JsonValue* JsonDict::getValue(std::string key)
{
	return _map[key];
}
std::string JsonValue::toStr()
{
	return "xxx";
}
std::string JsonValue::getStr()
{
	return "xxx";
}
std::string Json::ToStr()
{
	return root->toStr();
}
std::string Json::getStr()
{
	return root->getStr();
}
std::string JsonDict::toStr()
{
	std::string tmp;
	tmp += "{";
	for (int i = 0; i < dict_key.size(); ++i)
	{
		JsonValue* tmp_value = _map[dict_key[i]];
		tmp += "\"";
		tmp += dict_key[i];
		tmp += "\":";
		tmp += tmp_value->toStr();
		if (i != dict_key.size() - 1)
			tmp += ", ";
	}
	tmp += " }";
	return tmp;
}
std::string JsonDict::getStr()
{
	std::string tmp;
	tmp += "{";
	for (int i = 0; i < dict_key.size(); ++i)
	{
		JsonValue* tmp_value = _map[dict_key[i]];
		tmp += "\"";
		tmp += dict_key[i];
		tmp += "\":";
		tmp += tmp_value->getStr();
		if (i != dict_key.size() - 1)
			tmp += ", ";
	}
	tmp += " }";
	return tmp;
}
std::string JsonList::toStr()
{
	std::string tmp = "[ ";
	for (int i = 0; i < list.size(); ++i)
	{
		tmp += list[i]->toStr();

		if (i != list.size() - 1)
			tmp += ", ";
	}
	tmp += " ]";
	return tmp;
}
std::string JsonList::getStr()
{
	std::string tmp = "[ ";
	for (int i = 0; i < list.size(); ++i)
	{
		tmp += list[i]->toStr();

		if (i != list.size() - 1)
			tmp += ", ";
	}
	tmp += " ]";
	return tmp;
}
std::string JsonNumber::toStr()
{
	char buf[20] = "xxxx";
	double tmp = number;
	memset(buf, 0, sizeof(buf));
	_itoa(tmp, buf, 10);
	return buf;
}
std::string JsonNumber::getStr()
{
	char buf[20] = "xxxx";
	double tmp = number;
	memset(buf, 0, sizeof(buf));
	_itoa(tmp, buf, 10);
	return buf;
}
std::string JsonBool::toStr()
{
	if (Bool) return "true";
	else return "false";
}
std::string JsonBool::getStr()
{
	if (Bool) return "true";
	else return "false";
}
std::string JsonString::toStr()
{
	std::string tmp;
	tmp += "\"";
	for (int i = 0; i < str.size(); ++i)
	{
		switch (str[i])
		{
		case '"':
			tmp += "\"";
			break;
		case '\\':
			tmp += "\\";
			break;
		case '/':
			tmp += "/";
			break;
		case '\b':
			tmp += "\b";
			break;
		case '\f':
			tmp += "\f";
			break;
		case '\n':
			tmp += "\n";
			break;
		case '\r':
			tmp += "\r";
			break;
		case '\t':
			tmp += "\t";
			break;
		default:
			tmp += str[i];
			break;
		}
	}
	tmp += "\"";
	return tmp;
}
std::string JsonNull::toStr()
{
	return "null";
}
std::string JsonNull::getStr()
{
	return "null";
}
void JsonList::clear()
{
	std::vector<JsonValue*>::iterator i = list.begin();
	while (i != list.end())
	{
		delete (*i);
		++i;
	}
	list.clear();
}
void JsonDict::clear()
{
	std::unordered_map<std::string, JsonValue*>::iterator j = _map.begin();
	while (j != _map.end())
	{
		delete (j->second);
		j++;
	}
	_map.clear();
	dict_key.clear();
}
Jsontype JsonValue::getType()
{
	return type;
}
JsonValue* Json::getRoot()
{
	return root;
}
JsonList* JsonValue::toList()
{
	return NULL;
}
JsonDict* JsonValue::toDict()
{
	return NULL;
}
JsonList* JsonList::toList()
{
	return this;
}
JsonDict* JsonDict::toDict()
{
	return this;
}
int JsonDict::getSize()
{
	return dict_key.size();
}
std::string JsonString::getStr()
{
	return str;
}