#include"instance.h"

Instance::Instance() {

};

Instance::Instance(string &Instance_id, shared_ptr<App> &Refer_app, shared_ptr<Machine> &Refer_machine) {
	this->instance_id = Instance_id;
	this->refer_app = Refer_app;
	this->refer_machine = Refer_machine;
};

Instance::~Instance() {

};