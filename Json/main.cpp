#include <cstdlib>
#include "json.h"
#include <fstream>
#include <iostream>
using namespace std;
int main()
{

	ifstream fin("test.json");
	string str;
	Json json(&fin);      //��ʼ����
	cout << json.getRoot()->toDict()->getValue(4)->toDict()->toStr()<< endl; //����������
	system("pause");
	return 0;
}