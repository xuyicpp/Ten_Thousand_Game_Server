#pragma once
#include <queue>
#include <thread>
#include <pthread.h>
#include "Msg.h"
#include <string>


using namespace std;

class Service
{
public:
	uint32_t id;
	shared_ptr<string> type;
	bool isExiting = false;

	queue<shared_ptr<BaseMsg>> msgQueue;
	pthread_spinlock_t queueLock;
	
	Service();
	~Service();

	void OnInit();
	void OnMsg(shared_ptr<BaseMsg> msg);
	void OnExit();

	void PushMsg(shared_ptr<BaseMsg> msg);

	bool ProcessMsg();
	void ProcessMsgs(int max);

private:
	shared_ptr<BaseMsg> PopMsg();

public:
	bool inGlobal = false;
	pthread_spinlock_t inGlobalLock;
	void SetInGlobal(bool isIn);
};

