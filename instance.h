#pragma once
#ifndef INSTANCE_H
#define INSTANCE_H
#include"app.h"

using namespace std;

class Rachine;//��ǰ���ã���ֹ�໥����ͷ�ļ���ɱ������

class Instance {
public:
	string instance_id;
	shared_ptr<App> refer_app;
	shared_ptr<Rachine> refer_rachine;

	Instance();
	Instance(string &Instance_id, shared_ptr<App> &Refer_app, shared_ptr<Rachine> &Refer_rachine);
	~Instance();
};
#endif // !INSTANCE_H