#include"app.h"

//using命令：using std::cout;这样更加安全
App::App() {

};

App::App(string &App_id, float(&Cpu)[98], float(&Mem)[98], int &Disk, int &P, int &M, int &Pm, int &Inst_num,
	int &Inst_used, int &Priority, int &Transfer_flag, vector< tuple< App, int > > &App_inter) {
	std::make_shared< vector< tuple< App, int > > >();
	this->app_id = App_id;
	for (int num = 0; num < 98; num++) {
		this->cpu[num] = Cpu[num];
		this->mem[num] = Mem[num];
	};
	this->disk = Disk;
	this->p = P;
	this->m = M;
	this->pm = Pm;
	this->inst_num = Inst_num;
	this->inst_used = Inst_used;
	this->priority = Priority;
	this->transfer_flag = Transfer_flag;
	this->app_inter = App_inter;
};

App::~App() {

};