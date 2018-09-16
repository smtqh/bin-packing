#pragma once
#ifndef RACHINE_H
#define RACHINE_H
#include<string>
#include<memory>
#include"machine.h"

using namespace std;

class Instance;//超前引用，防止相互引用头文件造成编译错误

class Rachine {
public:
	string rachine_id;
	float cpu[1470];
	float mem[1470];
	int disk;
	float cpu_used[1470];
	float mem_used[1470];
	int disk_used;
	int p;
	int m;
	int pm;
	int p_used;
	int m_used;
	int pm_used;
	int load_num;
	vector< vector<Instance> > load_instance;
	vector<Load_Task> load_task;

	Rachine();
	Rachine(string &Rachine_id, float &Cpu, float &Mem, int &Disk, float &Cpu_used, float &Mem_used, int &Disk_used, int &P, int &M, 
		int &Pm, int &P_used, int &M_used, int &Pm_used, int &Load_num, vector< vector<Instance> > &Load_instance,
		vector<Load_Task> &Load_task);
	~Rachine();
};
#endif // !RACHINE_H

