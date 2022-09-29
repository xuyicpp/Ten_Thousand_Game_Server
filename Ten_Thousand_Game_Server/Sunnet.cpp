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
	pthread_rwlock_init(&servicesLock, NULL);
	pthread_spin_init(&globalLock, PTHREAD_PROCESS_PRIVATE);
	StartWorker();
}

void Sunnet::StartWorker() {
	for (int i = 0; i < WORKER_NUM; i++) {
		cout << "start worker thread:" << i << endl;
		Worker* worker = new Worker();
		worker->id = i;
		worker->eachNum = 2 << i;
		thread* wt = new thread(*worker);
		workers.push_back(worker);
		workerThreads.push_back(wt);
	}
}

void Sunnet::Wait() {
	if (workerThreads[0]) {
		workerThreads[0]->join();
	}
}

uint32_t Sunnet::NewService(shared_ptr<string> type) {
	auto srv = make_shared<Service>();
	srv->type = type;
	pthread_rwlock_wrlock(&servicesLock);
	{
		srv->id = maxId;
		maxId++;
		services.emplace(srv->id, srv);
	}
	pthread_rwlock_unlock(&servicesLock);
	srv->OnInit();
	return srv->id;
}

shared_ptr<Service> Sunnet::GetService(uint32_t id) {
	shared_ptr<Service> srv = NULL;
	pthread_rwlock_rdlock(&servicesLock);
	{
		unordered_map<uint32_t, shared_ptr<Service>>::iterator iter = services.find(id);
		if (iter != services.end()) {
			srv = iter->second;
		}
	}
	pthread_rwlock_unlock(&servicesLock);
	return srv;
}

void Sunnet::KillService(uint32_t id) {
	shared_ptr<Service> srv = GetService(id);
	if (!srv) {
		return;
	}

	srv->OnExit();
	srv->isExiting = true;

	pthread_rwlock_wrlock(&servicesLock);
	{
		services.erase(id);
	}
	pthread_rwlock_unlock(&servicesLock);
}

shared_ptr<Service> Sunnet::PopGlobalQueue() {
	shared_ptr<Service> srv = NULL;
	pthread_spin_lock(&globalLock);
	{
		if (!globalQueue.empty()) {
			srv = globalQueue.front();
			globalQueue.pop();
			globalLen--;
		}
	}
	pthread_spin_unlock(&globalLock);
	return srv;
}

void Sunnet::PushGlobalQueue(shared_ptr<Service> srv) {
	pthread_spin_lock(&globalLock);
	{
		globalQueue.push(srv);
		globalLen++;
	}
	pthread_spin_unlock(&globalLock);
}