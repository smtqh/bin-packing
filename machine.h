#pragma once
#ifndef MACHINE_H
#define MACHINE_H
#include"app.h"
#include"task.h"

using namespace std;

struct Load_App {
	shared_ptr<App> app;
	int num;
};

struct Num_Begin {
	int num;
	int begin_time;
};
struct Load_Task {
	shared_ptr<Task> task;
	vector< shared_ptr<Num_Begin> > num_begin;
};


class Machine {
private:
	string machine_id;
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
	Load_App load_app;
	Load_Task load_task;
public:
	Machine();
	Machine(string &Machine_id, float &Cpu, float &Mem, int &Disk, float &Cpu_used, float &Mem_used, int &Disk_used, 
		int &P, int &M, int &Pm, int &P_used, int &M_used, int &Pm_used, int &Load_num, Load_App &Load_app, Load_Task &Load_task);
	~Machine();
};
#endif // !MACHINE_H