#pragma once
#include"machine.h"
#include"rachine.h"

int read_machine(vector< shared_ptr<Machine> > &Machine_list, string name);
int read_rachine(vector< shared_ptr<Rachine> > &Rachine_list, string name);
int read_app(vector< shared_ptr<App> > &App_list);
int read_interference(vector< shared_ptr<App> > &App_list);
int read_instance(vector< shared_ptr<Instance> > &Instance_list, vector< shared_ptr<App> > &App_list, vector< shared_ptr<Rachine> > &Rachine_list, string name);
int read_Task(vector<Task> &Task);