#pragma once
#include <thread>
#include "Service.h"

using namespace std;

class Worker {
public:
	int id;
	int eachNum;
	void operator()();
	void CheckAndPutGlobal(shared_ptr<Service> srv);
};