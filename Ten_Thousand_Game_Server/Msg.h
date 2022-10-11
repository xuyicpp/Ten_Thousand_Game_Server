#pragma once
#include <memory>
using namespace std;

class BaseMsg
{
public:
	enum TYPE {
		SERVICE = 1,
	};

	int type;
	char load[99999999]{};	//用于检测内存泄漏，仅用于调试
	virtual ~BaseMsg() {};

};


class ServiceMsg :public BaseMsg {
public:
	int source; 
	shared_ptr<char> buff;
	size_t size;
	~ServiceMsg() {};
};
