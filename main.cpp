#include <cstdlib>
#include<iostream>
#include "fileUtil.h"

int main() {
	vector< shared_ptr<Machine> > machine_list;
	machine_list.reserve(8000);//machine���������������ǲ�һ����
	read_machine(machine_list, "a");
	vector< shared_ptr<Rachine> > rachine_list;
	rachine_list.reserve(8000);//machine���������������ǲ�һ����
	read_rachine(rachine_list, "a");
	vector< shared_ptr<App> > app_list;
	app_list.reserve(9338);//app����������������ݹ���һ��app_list
	read_app(app_list);
	read_interference(app_list);
	system("pause");
	return 0;
};