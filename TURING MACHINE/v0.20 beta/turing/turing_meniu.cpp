#include "turing_meniu.h"

#include "conio.h"

#include <iostream>



void turing_meniu::main_meniu() {
	sf::RenderWindow window(sf::VideoMode(1600, 410), "TURING");
	window.setFramerateLimit(60);
	arial.loadFromFile("arial.ttf");
	prepare_text();
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					for (int i = 0; i < max_threads; i++)
						if (button[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))) {
							std::cout << "Button " << i + 1 << " pressed " << std::endl;
							pressed = i;
							text[pressed].setString("(name)");
						}
				}
			}
			if (pressed != -1) upload(event);
		}
		get_turing_procesing_results();
		window.clear(sf::Color::Black);
		for (int i = 0; i < max_threads; i++) {
			window.draw(button[i]);
			window.draw(text[i]);
			window.draw(head_position[i]);
			window.draw(turing_task[i]);
			window.draw(step_text[i]);
			window.draw(steps[i]);
		}
		erase_strings();
		window.display();
	}
}





void turing_meniu::upload(sf::Event event)
{
	if (event.type == sf::Event::TextEntered)
	{
		if (event.text.unicode < 128)
		{
			temp_char = static_cast<char>(event.text.unicode);
			if (temp_char != 8) DUOM += temp_char;
			else DUOM = "";
			text[pressed].setString(DUOM);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		thread.start_task(pressed + 1, DUOM);
		text[pressed].setString("RUNNING");
		DUOM = "";
		pressed = -1;
	}
}

void turing_meniu::prepare_text()
{
	for (int i = 0; i < max_threads; i++) {
		button_text[button_text.size() - 1] = 49 + i;
		button[i].setSize(sf::Vector2f(160.0f, 40.0f));
		button[i].setPosition(10.0f, i * 50.0f + 10);
		text[i].setFont(arial);
		text[i].setString(button_text);
		text[i].setCharacterSize(30);
		text[i].setStyle(sf::Text::Bold);
		text[i].setFillColor(sf::Color::Red);
		text[i].setPosition(14.0f, i * 50.0f + 10);
		head_position[i].setFont(arial);
		head_position[i].setString("head_position");
		head_position[i].setCharacterSize(15);
		head_position[i].setStyle(sf::Text::Bold);
		head_position[i].setFillColor(sf::Color::Red);
		head_position[i].setPosition(300.0f, i * 50.0f + 10);
		turing_task[i].setFont(arial);
		turing_task[i].setString("turing_task");
		turing_task[i].setCharacterSize(15);
		turing_task[i].setStyle(sf::Text::Bold);
		turing_task[i].setFillColor(sf::Color::Red);
		turing_task[i].setPosition(300.0f, i * 50.0f + 30);
		step_text[i].setFont(arial);
		step_text[i].setString("steps");
		step_text[i].setCharacterSize(15);
		step_text[i].setStyle(sf::Text::Bold);
		step_text[i].setFillColor(sf::Color::Red);
		step_text[i].setPosition(220.0f, i * 50.0f + 10);
		steps[i].setFont(arial);
		steps[i].setString("step");
		steps[i].setCharacterSize(15);
		steps[i].setStyle(sf::Text::Bold);
		steps[i].setFillColor(sf::Color::Red);
		steps[i].setPosition(236.0f, i * 50.0f + 30);
	}
}

void turing_meniu::get_turing_procesing_results()
{
	for (int t = 1; t < max_threads; t++) {
		for (int i = thread.GETTER_head_position(t); i >= 0; i--) {
			if (i != 0)temp_head_position[t].push_back(95);
			else 	temp_head_position[t].push_back(32);

		}

		head_position[t - 1].setString(temp_head_position[t]);

		for (int i = 0; i < GETTER_turing_task(t).size(); i++) {
			temp_turing_task[t].push_back(GETTER_turing_task(t)[i]);
		}

		turing_task[t - 1].setString(temp_turing_task[t]);

		steps[t - 1].setString(std::to_string(GETTER_steps(t)));
		steps[t - 1].setPosition(240.0f - std::to_string(GETTER_steps(t)).size() * 4, (t - 1) * 50.0f + 30);

	}

}

void turing_meniu::erase_strings()
{
	for (int i = 1; i < max_threads; i++) {
		temp_head_position[i] = "";
		temp_turing_task[i] = "";
	}
}

void turing_meniu::CALL_stop_threads() {
	thread.stop_tasks();
}

std::vector<char> turing_meniu::GETTER_turing_task(int thread_number)
{
	return thread.GETTER_turing_task(thread_number);
}

int turing_meniu::GETTER_head_position(int thread_number)
{
	return thread.GETTER_head_position(thread_number);
}

int turing_meniu::GETTER_steps(int thread_number)
{
	return thread.GETTER_steps(thread_number);
}
