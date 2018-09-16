#include<iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include "fileUtil.h"

int read_machine(vector< shared_ptr<Machine> > &Machine_list, string name) {//对于字符串拼接，string可使用重载“+”，而char可使用C风格的stract（）函数
	ifstream inFile("data/machine_resources." + name + ".csv", ios::in); // 打开模式可省略vector< shared_ptr<Machine> >
	string lineStr;
	while (getline(inFile, lineStr)) {
		//cout << lineStr << endl;
		stringstream lineTra(lineStr);
		string str;
		vector<string> lineArray;
		while (getline(lineTra, str, ',')) {//在C++中，“”与‘’不同
			lineArray.push_back(str);
		};
		string Machine_id = lineArray[0];
		float Cpu;
		istringstream(lineArray[1]) >> Cpu;//强制转换，具有普适性的操作
		float Mem;
		istringstream(lineArray[2]) >> Mem;
		int Disk;
		istringstream(lineArray[3]) >> Disk;
		int P;
		istringstream(lineArray[4]) >> P;
		int M;
		istringstream(lineArray[5]) >> M;
		int Pm;
		istringstream(lineArray[6]) >> Pm;
		float Cpu_used = 0.0;
		float Mem_used = 0.0;
		int Disk_used = 0;
		int P_used = 0;
		int M_used = 0;
		int Pm_used = 0;
		int Load_num = 0;
		shared_ptr<Load_App> Load_app = std::make_shared<Load_App>();
		shared_ptr<Load_Task> Load_task = std::make_shared<Load_Task>();

		shared_ptr<Machine> machine = std::make_shared<Machine>(Machine_id, Cpu, Mem, Disk, Cpu_used, Mem_used, Disk_used,
			P, M, Pm, P_used, M_used, Pm_used, Load_num, Load_app, Load_task);

		Machine_list.push_back(machine);
	};
	return 0;
};

int read_rachine(vector< shared_ptr<Rachine> > &Rachine_list, string name) {//对于字符串拼接，string可使用重载“+”，而char可使用C风格的stract（）函数
	ifstream inFile("data/machine_resources." + name + ".csv", ios::in); // 打开模式可省略vector< shared_ptr<Machine> >
	string lineStr;
	while (getline(inFile, lineStr)) {
		//cout << lineStr << endl;
		stringstream lineTra(lineStr);
		string str;
		vector<string> lineArray;
		while (getline(lineTra, str, ',')) {//在C++中，“”与‘’不同
			lineArray.push_back(str);
		};
		string Rachine_id = lineArray[0];
		float Cpu;
		istringstream(lineArray[1]) >> Cpu;//强制转换，具有普适性的操作
		float Mem;
		istringstream(lineArray[2]) >> Mem;
		int Disk;
		istringstream(lineArray[3]) >> Disk;
		int P;
		istringstream(lineArray[4]) >> P;
		int M;
		istringstream(lineArray[5]) >> M;
		int Pm;
		istringstream(lineArray[6]) >> Pm;
		float Cpu_used = 0.0;
		float Mem_used = 0.0;
		int Disk_used = 0;
		int P_used = 0;
		int M_used = 0;
		int Pm_used = 0;
		int Load_num = 0;
		vector< vector<Instance> > Load_instance;
		vector<Load_Task> Load_task;

		shared_ptr<Rachine> rachine = std::make_shared<Rachine>(Rachine_id, Cpu, Mem, Disk, Cpu_used, Mem_used, Disk_used,
			P, M, Pm, P_used, M_used, Pm_used, Load_num, Load_instance, Load_task);

		Rachine_list.push_back(rachine);
	};
	return 0;
};

int read_app(vector< shared_ptr<App> > &App_list) {
	ifstream inFile("data/app_resources.csv", ios::in);
	string lineStr;
	while (getline(inFile, lineStr)) {
		//cout << lineStr << endl;
		stringstream lineTra(lineStr);
		string str;
		vector<string> lineArray;
		while (getline(lineTra, str, ',')) {//在C++中，“”与‘’不同
			lineArray.push_back(str);
		};
		string App_id = lineArray[0];
		regex reg("([0-9]+)");
		sregex_iterator cpu_list(lineArray[1].begin(), lineArray[1].end(), reg);//对CPU字符串进行匹配，分为98个时刻
		float Cpu[98];
		float cpu;
		int cpu_num = 0;
		for (auto one_cpu : *cpu_list) {
			istringstream(one_cpu.str()) >> cpu;
			Cpu[cpu_num] = cpu;
			cpu_num += 1;
		};
		sregex_iterator mem_list(lineArray[2].begin(), lineArray[2].end(), reg);
		float Mem[98];
		float mem;
		int mem_num = 0;
		for (auto one_mem : *mem_list) {
			istringstream(one_mem.str()) >> mem;
			Mem[mem_num] = mem;
			mem_num += 1;
		};
		int Disk;
		istringstream(lineArray[3]) >> Disk;
		int P;
		istringstream(lineArray[4]) >> P;
		int M;
		istringstream(lineArray[5]) >> M;
		int Pm;
		istringstream(lineArray[6]) >> Pm;
		int Inst_num = 0;
		int Inst_used = 0;
		int Priority = 0;
		int Transfer_flag = 0;
		vector< tuple< App, int > > App_inter;

		shared_ptr<App> app = std::make_shared<App>(App_id, Cpu, Mem, Disk, P, M, Pm, Inst_num,
			Inst_used, Priority, Transfer_flag, App_inter);

		App_list.push_back(app);
	};
	return 0;
};

int read_interference(vector< shared_ptr<App> > &App_list) {
	ifstream inFile("data/app_interference.csv", ios::in);
	string lineStr;
	while (getline(inFile, lineStr)) {
		//cout << lineStr << endl;
		stringstream lineTra(lineStr);
		string str;
		vector<string> lineArray;
		while (getline(lineTra, str, ',')) {//在C++中，“”与‘’不同
			lineArray.push_back(str);
		};
		int app_num;
		int inter_num;
		regex reg("([0-9]+)");
		smatch result;
		regex_search(lineArray[0], result, reg);
		//cout << result.str() << endl;
		istringstream(result.str()) >> app_num;
		regex_search(lineArray[1], result, reg);
		istringstream(result.str()) >> inter_num;
		int num;
		istringstream(lineArray[2]) >> num;
		tuple< App, int > App_inter;
		if (app_num == inter_num) {
			App_inter = make_tuple(*App_list[inter_num - 1], num + 1);
		}
		else {
			App_inter = make_tuple(*App_list[inter_num - 1], num);
		};

		(*App_list[app_num - 1]).app_inter.push_back(App_inter);
		//cout << get<1>(App_list[app_num - 1].app_inter[0]) << endl;
	};
	return 0;
};

int read_instance(vector< shared_ptr<Instance> > &Instance_list, vector< shared_ptr<App> > &App_list, vector< shared_ptr<Rachine> > &Rachine_list, string name) {//可以完成istance读取，app的补全
	ifstream inFile("data/instance_deploy." + name + ".csv", ios::in);
	string lineStr;
	while (getline(inFile, lineStr)) {
		//cout << lineStr << endl;
		stringstream lineTra(lineStr);
		string str;
		vector<string> lineArray;
		while (getline(lineTra, str, ',')) {//在C++中，“”与‘’不同
			lineArray.push_back(str);
		};
		int app_num;
		int rachine_num;
		string Instance_id = lineArray[0];
		regex reg("([0-9]+)");
		smatch result;
		regex_search(lineArray[1], result, reg);
		istringstream(lineArray[1]) >> app_num;//强制转换，具有普适性的操作
		regex_search(lineArray[2], result, reg);
		istringstream(lineArray[2]) >> rachine_num;//强制转换，具有普适性的操作
		shared_ptr<App> Refer_app = App_list[app_num - 1];
		shared_ptr<Rachine> Refer_rachine = Rachine_list[rachine_num - 1];
		shared_ptr<Instance> instance = std::make_shared<Instance>(Instance_id, Refer_app, Refer_rachine);
		Instance_list.push_back(instance);//构造Instance对象
		bool flag_load = false;
		for (int num = 0; num < ((*Rachine_list[rachine_num - 1]).load_instance).size(); num++) {//指针的嵌套关系十分复杂
			if ((((((*Rachine_list[rachine_num - 1]).load_instance)[num])[0]).refer_app) == Refer_app) {
			
			};
		};
		(*Rachine_list[rachine_num - 1]).load_instance;//将每个Instance加入对应的Rachine
	};
	return 0;
};