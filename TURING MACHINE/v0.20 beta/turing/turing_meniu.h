#pragma once
#include <iomanip>
#include "thread_managment.h"
#include <SFML/Graphics.hpp>


class turing_meniu: thread_managment
{
private:
	std::string button_text = "UPLOAD  ";
	std::string DUOM = "";
	int pressed = -1;
	char temp_char = 0;

	std::string temp_head_position[max_threads];
	std::string temp_turing_task[max_threads];

	sf::Font arial;

	sf::RectangleShape button[max_threads];
	sf::Text text[max_threads];
	sf::Text head_position[max_threads];
	sf::Text turing_task[max_threads];
	sf::Text steps[max_threads];
	sf::Text step_text[max_threads];

	thread_managment thread;
	int keyborad_input = 0;
public:
	void main_meniu();

	void upload(sf::Event event);
	void prepare_text();
	void get_turing_procesing_results();
	void erase_strings ();

	void CALL_stop_threads();

	std::vector<char> GETTER_turing_task(int thread_number);
	int GETTER_head_position(int thread_number);
	int GETTER_steps(int thread_number);
};

