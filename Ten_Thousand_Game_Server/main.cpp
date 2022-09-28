#include "Sunnet.h"

void test() {
	auto pingType = make_shared<string>("ping");
	uint32_t ping1 = Sunnet::inst->NewService(pingType);
	uint32_t ping2 = Sunnet::inst->NewService(pingType);
	uint32_t pong = Sunnet::inst->NewService(pingType);
}

int main()
{
	new Sunnet();
	Sunnet::inst->Start();
	//开启系统后的一些逻辑
	test();
	Sunnet::inst->Wait();
	return 0;
}