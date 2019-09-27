#include "thread_managment.h"

void thread_managment::start_task(int thread_number, std::string DUOM) {
	printf("%d", thread_number);
	th[thread_number] = std::thread(&thread_managment::TEMP_test, this, thread_number, DUOM);
}

void thread_managment::stop_tasks() {
	for (int i = 0; i < max_threads; i++)
		if(thread_ended[i]==true) th[i].join();
}

void thread_managment::TEMP_test(int thread_number, std::string DUOM)
{
	engine[thread_number].start_processing(thread_number, DUOM);
}



std::vector<char> thread_managment::GETTER_turing_task(int thread_number)
{
	return engine[thread_number].RETURNER_turing_task();
}

int thread_managment::GETTER_head_position(int thread_number)
{
	return engine[thread_number].RETURNER_head_position();
}

int thread_managment::GETTER_steps(int thread_number)
{
	return engine[thread_number].RETURNER_steps();
}
