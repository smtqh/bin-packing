#pragma once
#ifndef INSTANCE_H
#define INSTANCE_H
#include"machine.h"

using namespace std;

class Instance {
private:
	string instance_id;
	shared_ptr<App> refer_app;
	shared_ptr<Machine> refer_machine;
public:
	Instance();
	Instance(string &Instance_id, shared_ptr<App> &Refer_app, shared_ptr<Machine> &Refer_machine);
	~Instance();
};
#endif // !INSTANCE_H