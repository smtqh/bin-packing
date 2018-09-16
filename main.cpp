#include <cstdlib>
#include<iostream>
#include "fileUtil.h"

int main() {
	vector< shared_ptr<Machine> > machine_list;
	machine_list.reserve(8000);//machine数量，各个数据是不一样的
	read_machine(machine_list, "a");
	vector< shared_ptr<Rachine> > rachine_list;
	rachine_list.reserve(8000);//machine数量，各个数据是不一样的
	read_rachine(rachine_list, "a");
	vector< shared_ptr<App> > app_list;
	app_list.reserve(9338);//app数量，针对所有数据公用一个app_list
	read_app(app_list);
	read_interference(app_list);
	system("pause");
	return 0;
};