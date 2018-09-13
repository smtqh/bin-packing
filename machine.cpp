#include"machine.h"

Machine::Machine() {

};

Machine::Machine(string &Machine_id, float &Cpu, float &Mem, int &Disk, float &Cpu_used, float &Mem_used,
	int &Disk_used, int &P, int &M, int &Pm, int &P_used, int &M_used, int &Pm_used, int &Load_num, 
	Load_App &Load_app, Load_Task &Load_task) {
	std::make_shared<Task>();
	std::make_shared<App>();
	std::make_shared<Num_Begin>();
	this->machine_id = Machine_id;
	for (int num = 0; num < 1470; num++) {
		this->cpu[num] = Cpu;
		this->mem[num] = Mem;
		this->cpu_used[num] = Cpu_used;
		this->mem_used[num] = Mem_used;
	};
	this->disk = Disk;
	this->disk_used = Disk_used;
	this->p = P;
	this->m = M;
	this->pm = Pm;
	this->p_used = P_used;
	this->m_used = M_used;
	this->pm_used = Pm_used;
	this->load_num = Load_num;
	this->load_app = Load_app;
	this->load_task = Load_task;
};

Machine::~Machine() {

};