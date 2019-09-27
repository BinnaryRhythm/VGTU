#pragma once

#include "machine_input.h"
#include <string>
#include <vector>

class turing_machine: machine_input
{
private:
	machine_input input;

	int head_position=0;
	std::vector<char> turing_task;
	std::vector<std::string> turing_instructions;
	int steps = 0;

	std::string curret_state = "0";

	std::string state[100];
	char curret_symbol[100];
	char new_symbol[100];
	char direction[100];
	std::string new_state[100];

	int temp = 0;
	bool found = false;
	bool halt = false;

public:
	void start_processing(int thread_number, std::string DUOM);
	void upload_turing_problem(std::string DUOM);
	void splitup_turing_task();
	void processing_logic();
	
	
	void add_extra_size_to_head_position();
	void move_head_position(int i);
	void search_rule_for_needed_symbols();
	void search_rule_for_all_symbols();
	void didint_found_any_rule();

	void TEMP_show_info(int i);		

	std::vector<char> RETURNER_turing_task();
	int RETURNER_head_position();
	int RETURNER_steps();
};

