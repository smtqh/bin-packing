#include"task.h"

Task::Task() {

};

Task::Task(string &Task_id, float &Cpu, float &Mem, int &Inst_num, int &Inst_used, int &Time_length, int &Min_begin,
	int &Max_begin, int &Real_min, int &Real_max, vector<shared_ptr<Task>> &Front_task, vector<shared_ptr<Task>> &After_task) {
	std::make_shared< vector<Task> >();
	std::make_shared< vector<Task> >();
	this->task_id = Task_id;
	this->cpu = Cpu;
	this->mem = Mem;
	this->inst_num = Inst_num;
	this->inst_used = Inst_used;
	this->time_length = Time_length;
	this->min_begin = Min_begin;
	this->max_begin = Max_begin;
	this->real_min = Real_min;
	this->real_max = Real_max;
	this->front_task = Front_task;
	this->after_task  = After_task;
};

Task::~Task() {

};