#pragma once
#include <vector>
#include "Worker.h"

class Sunnet {
public:
	//单例
	static Sunnet* inst;
public:
	//构造函数
	Sunnet();
	//初始化并开始
	void Start();
	void Wait();
private:
	int WORKER_NUM = 3;
	vector<Worker*> workers;
	vector<thread*> workerThreads;
private:
	void StartWorker();
};