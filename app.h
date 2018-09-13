#pragma once
#ifndef APP_H
#define APP_H
#include<string>
#include<vector>
#include<tuple>

using namespace std;

class App {
private:
	string app_id;
	float cpu[1470];
	float mem[1470];
	int disk;
	int p;
	int m;
	int pm;
	int inst_num;
	int inst_used;
	int priority;
	int transfer_flag;
	tuple< shared_ptr<App>, int > app_inter;//Ӧ��ʹ��ָ�룬��Ϊģ�����Ҫ�����������������ͣ���ֱ����APP�Ļ���û��ʼ��������ѭ��
public:
	App();
	App(string &App_id, float (&Cpu)[98], float (&Mem)[98], int &Disk, int &P, int &M, int &Pm, int &Inst_num, 
		int &Inst_used, int &Priority, int &Transfer_flag, tuple< shared_ptr<App>, int > &App_inter);//����д��&Cpu[98]����Ϊ�±�����ȼ���
	~App();
};
#endif // !APP_H