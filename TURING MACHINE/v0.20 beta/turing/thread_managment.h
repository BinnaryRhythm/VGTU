#pragma once

#include <thread>
#include <vector>
#include "turing_machine.h"

const int max_threads = 8+1;

class thread_managment: turing_machine
{
private:
	turing_machine engine[max_threads];
	std::thread th[max_threads];
	bool thread_ended[max_threads] = { 0 };
public:
	void start_task(int thread_number, std::string DUOM);
	void stop_tasks();
	void TEMP_test(int thread_number, std::string DUOM);

	std::vector<char> GETTER_turing_task(int thread_number);
	int GETTER_head_position(int thread_number);
	int GETTER_steps(int thread_number);
};

