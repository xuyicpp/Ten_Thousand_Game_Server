#pragma once
#include <thread>

using namespace std;

class Worker {
public:
	int id;
	int eachNum;
	void operator()();
};