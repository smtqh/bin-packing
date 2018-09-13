#include"app.h"

//using命令：using std::cout;这样更加安全
App::App() {

};

App::App(string &App_id, float(&Cpu)[98], float(&Mem)[98], int &Disk, int &P, int &M, int &Pm, int &Inst_num,
	int &Inst_used, int &Priority, int &Transfer_flag, tuple<shared_ptr<App>, int> &App_inter) {
	this->app_id = App_id;
	for (int num = 0; num < 1470; num++) {
		this->cpu[num] = Cpu[num / 15];
		this->mem[num] = Mem[num / 15];
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