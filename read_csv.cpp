#include<iostream>
#include <fstream>
#include <sstream>
#include"machine.h"

int read_machine(vector<Machine> &Machine_list, string name) {//对于字符串拼接，string可使用重载“+”，而char可使用C风格的stract（）函数
	ifstream inFile("data/machine_resources." + name + ".csv", ios::in); // 打开模式可省略vector< shared_ptr<Machine> >
	string lineStr;
	while (getline(inFile, lineStr)) {
		cout << lineStr << endl;
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

		Machine machine(Machine_id, Cpu, Mem, Disk, Cpu_used, Mem_used, Disk_used,
			P, M, Pm, P_used, M_used, Pm_used, Load_num, Load_app, Load_task);
		Machine_list.push_back(machine);
	};
	return 0;
};