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
	char load[99999999]{};	//���ڼ���ڴ�й©�������ڵ���
	virtual ~BaseMsg() {};

};


class ServiceMsg :public BaseMsg {
public:
	int source; 
	shared_ptr<char> buff;
	size_t size;
	~ServiceMsg() {};
};
