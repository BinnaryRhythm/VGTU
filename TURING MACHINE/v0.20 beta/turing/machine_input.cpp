#include "machine_input.h"
#include <iostream>

machine_input::machine_input(void) {
}
machine_input::~machine_input(void) {
}

void machine_input::open_file(std::string DUOM)
{
	file.open(DUOM);
}
void machine_input::done()
{
	file.close();
}


int machine_input::get_head_position()
{	
	file >> temp;
	return temp-1;
}
std::vector<char> machine_input::read_task()
{
	file >> temp_turing_task;
	for (int i = 0; i < temp_turing_task.size(); i++) {
		turing_task.push_back(temp_turing_task[i]);
	}
	return turing_task;
}
std::vector<std::string> machine_input::read_instructions()
{
	temp = 0;
	while (std::getline(file, temp_turing_instructions)) {
		if (temp_turing_instructions[0] != 0) turing_instructions.push_back(temp_turing_instructions);
		temp++;
	}
	return turing_instructions;
}
