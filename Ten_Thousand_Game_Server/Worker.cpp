#include <iostream>
#include "Worker.h"

using namespace std;

void Worker::operator()() {
	while (true)
	{
		cout << "woking id:" << id << endl;
		this_thread::sleep_for(std::chrono::milliseconds(2000));
	}
}