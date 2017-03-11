#include <cstdlib>
#include "json.h"
#include <fstream>
#include <iostream>
using namespace std;
int main()
{

	ifstream fin("test.json");
	string str;
	Json json(&fin);      //开始解析
	cout << json.getRoot()->toDict()->getValue(4)->toDict()->toStr()<< endl; //输出解析结果
	system("pause");
	return 0;
}