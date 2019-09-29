#include "thread_managment.h"
#include <chrono>

void thread_managment::init_engine() {
	for (int i = 1; i < max_threads; i++) {
		engine[i] = new turing_machine[1];
	}
}

void thread_managment::start_task(int thread_number, std::string DUOM) {
	printf("%d", thread_number);
	th[thread_number] = new std::thread[1];
	th[thread_number][0] = std::thread(&thread_managment::TEMP_test, this, thread_number, DUOM);
}

void thread_managment::stop_tasks() {
	for (int i = 0; i < max_threads; i++)
		if(thread_ended[i]==true) th[i][0].join();
}

void thread_managment::TEMP_test(int thread_number, std::string DUOM)
{
	engine[thread_number][0].start_processing(thread_number, DUOM);
}

void thread_managment::pause_resume(int thread_number)
{
	engine[thread_number][0].pause_resume();
}


void thread_managment::STOP_engine(int thread_number)
{
	engine[thread_number][0].stop_procesing();
	th[thread_number][0].join();
	delete[] engine[thread_number];
	engine[thread_number] = new turing_machine[1];
	delete[] th[thread_number];

}

std::vector<char> thread_managment::GETTER_turing_task(int thread_number)
{
	return engine[thread_number][0].RETURNER_turing_task();
}

int thread_managment::GETTER_head_position(int thread_number)
{
	return engine[thread_number][0].RETURNER_head_position();
}

int thread_managment::GETTER_steps(int thread_number)
{
	return engine[thread_number][0].RETURNER_steps();
}

