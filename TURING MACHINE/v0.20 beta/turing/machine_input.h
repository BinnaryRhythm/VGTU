#pragma once
#include <string>
#include <fstream>
#include <vector>

class machine_input
{
private:
	std::string DUOM;
	std::ifstream file;

	std::vector<char> turing_task;
	std::vector<std::string> turing_instructions;

	int instructions_length = 0;

	std::string temp_turing_task;
	std::string temp_turing_instructions;
	int temp = 0;


public:
	machine_input();
	~machine_input();

	void open_file(std::string DUOM);
	void done();

	int get_head_position();
	std::vector<char> read_task();
	std::vector<std::string> read_instructions();



};

