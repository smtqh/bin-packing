#pragma once
#ifndef TASK_H
#define TASK_H
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Task {
private:
	string task_id;
	float cpu;
	float mem;
	int inst_num;
	int inst_used;
	int time_length;
	int min_begin;
	int max_begin;
	int real_min;
	int real_max;
	vector<shared_ptr<Task>> front_task;
	vector<shared_ptr<Task>> after_task;
public:
	Task();
	Task(string &Task_id, float &Cpu, float &Mem, int &Inst_num, int &Inst_used, int &Time_length, int &Min_begin,
		int &Max_begin, int &Real_min, int &Real_max, vector<shared_ptr<Task>> &Front_task, vector<shared_ptr<Task>> &After_task);
	~Task();
};
#endif // !TASK_H