#include "instance.h"
#include "rachine.h"
#include "app.h"

Instance::Instance() {

};

Instance::Instance(string &Instance_id, shared_ptr<App> &Refer_app, shared_ptr<Rachine> &Refer_rachine) {
	std::make_shared<App>();
	std::make_shared<Rachine>();
	this->instance_id = Instance_id;
	this->refer_app = Refer_app;
	this->refer_rachine = Refer_rachine;
};

Instance::~Instance() {

};