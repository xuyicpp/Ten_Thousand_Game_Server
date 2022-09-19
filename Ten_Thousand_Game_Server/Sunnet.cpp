#include <iostream>
#include "Sunnet.h"

using namespace std;

//单例
Sunnet* Sunnet::inst;
Sunnet::Sunnet() {
	inst = this;
}

//开启系统
void Sunnet::Start() {
	cout << "Hello Sunnet" << endl;
}