#pragma once

class Sunnet {
public:
	//单例
	static Sunnet* inst;
public:
	//构造函数
	Sunnet();
	//初始化并开始
	void Start();
};