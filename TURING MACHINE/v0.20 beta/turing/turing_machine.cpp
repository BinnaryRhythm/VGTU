#include <iostream>
#include "turing_machine.h"
#include "conio.h"

#include <thread>
#include <chrono>

const int speed = 50;

using namespace std;

void turing_machine::start_processing(int thread_number, std::string DUOM)
{
	upload_turing_problem(DUOM);
	splitup_turing_task();
	processing_logic();
}

void  turing_machine::upload_turing_problem(std::string DUOM)
{
	input.open_file(DUOM);
	head_position = input.get_head_position();
	turing_task = input.read_task();
	turing_instructions = input.read_instructions();
	input.done();
}

void turing_machine::splitup_turing_task()
{
	for (int i = 0; i < turing_instructions.size(); i++) {
		temp = 0;
		while (turing_instructions[i][temp]!=32) {
			state[i]+=turing_instructions[i][temp];
			temp++;
		}
		temp++;
		while (turing_instructions[i][temp] != 32) {
			curret_symbol[i] = turing_instructions[i][temp];
			temp++;
		}
		temp++;
		while (turing_instructions[i][temp] != 32) {
			new_symbol[i] = turing_instructions[i][temp];
			temp++;
		}
		temp++;
		while (turing_instructions[i][temp] != 32) {
			direction[i] = turing_instructions[i][temp];
			temp++;
		}
		temp++;
		while (temp != turing_instructions[i].size()&& turing_instructions[i][temp]!=32) {
			new_state[i] += turing_instructions[i][temp];
			temp++;
		}
	}
}

void turing_machine::processing_logic()
{
	found = false;
	halt = false;
	steps = 0;
	while (halt==false) 
	{
		found = false;
		search_rule_for_needed_symbols();
		if (found == false) search_rule_for_all_symbols();
		if (found == false) didint_found_any_rule();
	}
}









void turing_machine::add_extra_size_to_head_position()
{
	if (head_position == 0)
	{
		turing_task.insert(turing_task.begin(), 32);
		head_position++;
	}
	else if (head_position == turing_task.size())
	{
		turing_task.insert(turing_task.end(), 32);
	}
}

void turing_machine::move_head_position(int i)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(speed));
	steps++;
	if ((int)direction[i] == 108 || (int)direction[i] == 76)
	{
		head_position--;
	}
	else if ((int)direction[i] == 82 || (int)direction[i] == 114)
	{
		head_position++;
	}
}

void turing_machine::search_rule_for_needed_symbols()
{
	for (int i = 0; i < turing_instructions.size(); i++)
	{
		add_extra_size_to_head_position();
		if (state[i] == curret_state)
		{
			if (turing_task[head_position] == curret_symbol[i]) {
				found = true;
				TEMP_show_info(i);
				if ((int)new_symbol[i] != 42)
				{
					turing_task[head_position] = new_symbol[i];
				}
				move_head_position(i);
				curret_state = new_state[i];
				i = 0;
			}
		}
	}
}

void turing_machine::search_rule_for_all_symbols()
{
	for (int i = 0; i < turing_instructions.size(); i++)
	{
		add_extra_size_to_head_position();
		if (state[i] == curret_state)
		{
			if (curret_symbol[i] == 42)
			{
				found = true;
				TEMP_show_info(i);
				if ((int)new_symbol[i] != 42)
				{
					turing_task[head_position] = new_symbol[i];
				}
				move_head_position(i);
				curret_state = new_state[i];
				i = turing_instructions.size();
			}
		}

	}
}

void turing_machine::didint_found_any_rule()
{
	cout << "\nHalted. No rule for statement " << curret_state << " and symbol " << turing_task[head_position] << ".";
	halt = true;
}

void turing_machine::TEMP_show_info(int i)
{/*
	cout <<"step "<< steps<< "\n";
	
	for (int x = 0; x < turing_task.size(); x++)
	{
		if (x != head_position) cout << " ";
		else cout << "_";
	}
	cout << endl;
	for (int x = 0; x < turing_task.size(); x++)
		cout << turing_task[x];
	cout << endl << endl;
*/}

std::vector<char> turing_machine::RETURNER_turing_task()
{
	return turing_task;
}

int turing_machine::RETURNER_head_position()
{
	return head_position;
}

int turing_machine::RETURNER_steps()
{
	return steps;
}
