#include <cstdlib>
#include "fileUtil.h"

int main() {
	vector<Machine> machine_list;
	machine_list.reserve(8000);
	read_machine(machine_list, "a");
	//getchar();
	system("pause");
	return 0;
};