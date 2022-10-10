#include <iostream>
#include "Worker.h"
#include "Service.h"
#include "Sunnet.h"

using namespace std;

void Worker::operator()() {
	while (true)
	{
		shared_ptr<Service> srv = Sunnet::inst->PopGlobalQueue();
		if (!srv) {
			this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		else {
			srv->ProcessMsgs(eachNum);
			CheckAndPutGlobal(srv);
		}
	}
}

void Worker::CheckAndPutGlobal(shared_ptr<Service> srv) {
	if (srv->isExiting) {
		return;
	}
	pthread_spin_lock(&srv->queueLock);
	{
		if (!srv->msgQueue.empty()) {
			Sunnet::inst->PushGlobalQueue(srv);
		}
		else {
			srv->SetInGlobal(false);
		}
	}
	pthread_spin_unlock(&srv->queueLock);
}

