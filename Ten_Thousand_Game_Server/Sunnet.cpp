#include <iostream>
#include "Sunnet.h"

using namespace std;

//����
Sunnet* Sunnet::inst;
Sunnet::Sunnet() {
	inst = this;
}

//����ϵͳ
void Sunnet::Start() {
	cout << "Hello Sunnet" << endl;
}