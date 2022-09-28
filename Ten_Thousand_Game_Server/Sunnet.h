#pragma once
#include <vector>
#include "Worker.h"
#include <unordered_map>
#include "Service.h"

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

public:
	unordered_map<uint32_t, shared_ptr<Service>> services;
	uint32_t maxId = 0;
	pthread_rwlock_t servicesLock;
public:
	uint32_t NewService(shared_ptr<string> type);
	void KillService(uint32_t id);
private:
	shared_ptr<Service> GetService(uint32_t id);
};