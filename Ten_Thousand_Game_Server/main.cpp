#include "Sunnet.h"

int main()
{
	new Sunnet();
	Sunnet::inst->Start();
	//����ϵͳ���һЩ�߼�
	Sunnet::inst->Wait();
	return 0;
}