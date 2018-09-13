#include"stdlib.h"
#include"read_csv.cpp"

int main() {
	vector<Machine> machine_list;
	machine_list.reserve(8000);
	read_machine(machine_list, "a");
	//getchar();
	system("pause");
	return 0;
};