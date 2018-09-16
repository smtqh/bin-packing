#include "rachine.h"
#include "instance.h"

Rachine::Rachine() {

};

Rachine::Rachine(string &Rachine_id, float &Cpu, float &Mem, int &Disk, float &Cpu_used, float &Mem_used, 
	int &Disk_used, int &P, int &M, int &Pm, int &P_used, int &M_used, int &Pm_used, int &Load_num, 
	vector< vector<Instance> > &Load_instance, vector<Load_Task> &Load_task) {
	std::make_shared<Num_Begin>();
	std::make_shared<Instance>();
	std::make_shared<Task>();
	std::make_shared<Load_Task>();
	std::make_shared< vector<Instance> >();
	std::make_shared< vector<Load_Task> >();
	std::make_shared< vector< vector<Instance> > >();
	this->rachine_id = Rachine_id;
	for (int num = 0; num < 1470; num++) {
		this->cpu[num] = Cpu;
		this->mem[num] = Mem;
		this->cpu_used[num] = Cpu_used;
		this->mem_used[num] = Mem_used;
	};
	this->disk;
	this->disk_used;
	this->p;
	this->m;
	this->pm;
	this->p_used;
	this->m_used;
	this->pm_used;
	this->load_num;
	this->load_instance;
	this->load_task;
};

Rachine::~Rachine() {

};