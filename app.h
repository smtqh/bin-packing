#pragma once
#ifndef APP_H
#define APP_H
#include<string>
#include<vector>
#include<tuple>

using namespace std;

class App {
public:
	string app_id;
	float cpu[98];
	float mem[98];
	int disk;
	int p;
	int m;
	int pm;
	int inst_num;
	int inst_used;
	int priority;
	int transfer_flag;
	vector< tuple< App, int > > app_inter;//应该使用指针，因为模板参数要求的是完整定义的类型，而直接用APP的话还没初始化，会死循环
	
	App();
	App(string &App_id, float (&Cpu)[98], float (&Mem)[98], int &Disk, int &P, int &M, int &Pm, int &Inst_num, 
		int &Inst_used, int &Priority, int &Transfer_flag, vector< tuple< App, int > > &App_inter);//不能写成&Cpu[98]，因为下标的优先级高
	~App();
};
#endif // !APP_H