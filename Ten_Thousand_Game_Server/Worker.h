#pragma once
#include <thread>

using namespace std;

class Worker {
public:
	int id;
	int eachNum;
	void operator()();
	void CheckAndPutGlobal(shared_ptr<Service> srv);
};