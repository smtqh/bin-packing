#include<iostream>
#include <fstream>
#include <sstream>
#include"machine.h"

int read_machine(vector<Machine> &Machine_list, string name) {//�����ַ���ƴ�ӣ�string��ʹ�����ء�+������char��ʹ��C����stract��������
	ifstream inFile("data/machine_resources." + name + ".csv", ios::in); // ��ģʽ��ʡ��vector< shared_ptr<Machine> >
	string lineStr;
	int machine_num = 0;
	while (getline(inFile, lineStr)) {
		cout << lineStr << endl;
		stringstream lineTra(lineStr);
		string str;
		vector<string> lineArray;
		while (getline(lineTra, str, ',')) {//��C++�У������롮����ͬ
			lineArray.push_back(str);
		};
		string Machine_id = lineArray[0];
		float Cpu;
		istringstream(lineArray[1]) >> Cpu;//ǿ��ת�������������ԵĲ���
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
		Load_App Load_app;
		Load_Task Load_task;

		Machine machine(Machine_id, Cpu, Mem, Disk, Cpu_used, Mem_used, Disk_used,
			P, M, Pm, P_used, M_used, Pm_used, Load_num, Load_app, Load_task);
		Machine_list[machine_num] = machine;
		machine_num += 1;
	};
	return 0;
};